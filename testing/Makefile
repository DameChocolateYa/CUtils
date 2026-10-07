TARGET := test

BUILD := build
SOURCES := src
INCLUDES := include

CC := gcc
CFLAGS := -Wall -Werror -O2 -I$(INCLUDES)
LDFLAGS := -lcstring

CFILES := $(wildcard $(SOURCES)/*.c)
OFILES := $(CFILES:$(SOURCES)/%.c=$(BUILD)/%.o)

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OFILES)
	@echo "Linking $@"
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD)/%.o: $(SOURCES)/%.c
	@mkdir -p $(BUILD)
	@echo "Compiling $<"
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf $(TARGET) $(BUILD)

rebuild: clean all