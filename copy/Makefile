TARGET := cstring

BUILD := build
SOURCES := src
INCLUDES := include

CC := gcc
CFLAGS := -Wall -Werror -O2 -fPIC
LDFLAGS := -shared

CFILES := $(wildcard $(SOURCES)/*.c)
OFILES := $(CFILES:$(SOURCES)/%.c=$(BUILD)/%.o)

.PHONY: all clean rebuild install remove

all: lib$(TARGET).so

lib$(TARGET).so: $(OFILES)
	@echo "Linking $@"
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD)/%.o: $(SOURCES)/%.c
	@mkdir -p $(BUILD)
	@echo "Compiling $<"
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf lib$(TARGET).so $(BUILD)

rebuild: clean all

install: lib$(TARGET).so
	@echo "Installing..."
	@cp $< /usr/lib/
	@mkdir -p /usr/include/$(TARGET)
	@cp -r $(INCLUDES)/* /usr/include/$(TARGET)/

remove:
	@echo "Removing..."
	@rm -f /usr/lib/lib$(TARGET).so
	@rm -rf /usr/include/$(TARGET)