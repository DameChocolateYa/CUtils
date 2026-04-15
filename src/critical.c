#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int uint64_to_str(uint64_t n, int base, char *buf, int bufsize) {
  const char *digits = "0123456789abcdef";
  char tmp[32];
  int i = 0;
  if (n == 0) {
    if (bufsize > 0)
      buf[0] = '0';
    return 1;
  }
  while (n > 0 && i < 32) {
    tmp[i++] = digits[n % base];
    n /= base;
  }
  int len = 0;
  while (i > 0 && len < bufsize) {
    buf[len++] = tmp[--i];
  }
  return len;
}

static int int_to_str(int n, char *buf, int bufsize) {
  if (n < 0) {
    if (bufsize > 0)
      buf[0] = '-';
    int len = uint64_to_str((uint64_t)(-n), 10, buf + 1, bufsize - 1);
    return len + 1;
  } else {
    return uint64_to_str((uint64_t)n, 10, buf, bufsize);
  }
}

static int ptr_to_str(void *ptr, char *buf, int bufsize) {
  if (bufsize < 3)
    return 0;
  buf[0] = '0';
  buf[1] = 'x';
  int len = uint64_to_str((uintptr_t)ptr, 16, buf + 2, bufsize - 2);
  return len + 2;
}

static int double_to_str(double val, int precision, char *buf, int bufsize) {
  if (precision < 0)
    precision = 6;

  int len = 0;
  if (val < 0) {
    if (len < bufsize)
      buf[len++] = '-';
    val = -val;
  }

  long long intpart = (long long)val;
  double frac = val - (double)intpart;

  char tmp[64];
  int intlen = int_to_str(intpart, tmp, sizeof(tmp));
  if (len + intlen >= bufsize)
    intlen = bufsize - len;
  memcpy(buf + len, tmp, intlen);
  len += intlen;

  if (precision > 0 && len < bufsize) {
    buf[len++] = '.';
    for (int i = 0; i < precision && len < bufsize; i++) {
      frac *= 10.0;
      int digit = (int)frac;
      buf[len++] = '0' + digit;
      frac -= digit;
    }
  }

  if (len < bufsize)
    buf[len] = '\0';
  return len;
}

// <-- VISIBLE PART BY STRING.H --> //

char *strbuf(const char *fmt, int *len_r, va_list args) {
  int capacity = 256;
  char *out = (char *)malloc(capacity);
  if (!out)
    return NULL;
  int pos = 0;

  const char *p = fmt;
  while (*p) {
    int precision = 6;

    if (*p != '%') {
      if (pos >= capacity) {
        capacity *= 2;
        out = (char *)realloc(out, capacity);
      }
      out[pos++] = *p++;
      continue;
    }

    p++;

    if (*p == '.') {
      p++;
      precision = 0;
      while (*p >= '0' && *p <= '9') {
        precision = precision * 10 + (*p - '0');
        p++;
      }
    }

    if (*p == '\0')
      break;

    char tmp[128];
    int len = 0;

    switch (*p) {
    case 's': {
      char *s = va_arg(args, char *);
      if (!s)
        s = "(nil)";
      for (int i = 0; s[i]; i++) {
        if (pos >= capacity) {
          capacity *= 2;
          out = (char *)realloc(out, capacity);
        }
        out[pos++] = s[i];
      }
      break;
    }
    case 'd': {
      int d = va_arg(args, int);
      len = int_to_str(d, tmp, sizeof(tmp));
      for (int i = 0; i < len; i++) {
        if (pos >= capacity) {
          capacity *= 2;
          out = (char *)realloc(out, capacity);
        }
        out[pos++] = tmp[i];
      }
      break;
    }
    case 'x': {
      unsigned int x = va_arg(args, unsigned int);
      len = uint64_to_str(x, 16, tmp, sizeof(tmp));
      for (int i = 0; i < len; i++) {
        if (pos >= capacity) {
          capacity *= 2;
          out = (char *)realloc(out, capacity);
        }
        out[pos++] = tmp[i];
      }
      break;
    }
    case 'p': {
      void *ptr = va_arg(args, void *);
      len = ptr_to_str(ptr, tmp, sizeof(tmp));
      for (int i = 0; i < len; i++) {
        if (pos >= capacity) {
          capacity *= 2;
          out = (char *)realloc(out, capacity);
        }
        out[pos++] = tmp[i];
      }
      break;
    }
    case 'f': {
      double f = va_arg(args, double);
      len = double_to_str(f, precision, tmp, sizeof(tmp));
      for (int i = 0; i < len; i++) {
        if (pos >= capacity) {
          capacity *= 2;
          out = (char *)realloc(out, capacity);
        }
        out[pos++] = tmp[i];
      }
      break;
    }
    case 'c': {
      char c = (char)va_arg(args, int);
      if (pos >= capacity) {
        capacity *= 2;
        out = (char *)realloc(out, capacity);
      }
      out[pos++] = c;
      break;
    }
    case '%': {
      if (pos >= capacity) {
        capacity *= 2;
        out = (char *)realloc(out, capacity);
      }
      out[pos++] = '%';
      break;
    }
    default: {
      if (pos >= capacity) {
        capacity *= 2;
        out = (char *)realloc(out, capacity);
      }
      out[pos++] = '%';
      if (pos >= capacity) {
        capacity *= 2;
        out = (char *)realloc(out, capacity);
      }
      out[pos++] = *p;
      break;
    }
    }

    p++;
  }

  if (pos >= capacity) {
    capacity += 1;
    out = (char *)realloc(out, capacity);
  }
  out[pos] = '\0';
  *len_r = pos;
  return out;
}