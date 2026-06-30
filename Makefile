CC      = gcc
CFLAGS  = -g -Wall -lraylib
LDFLAGS = -lraylib
TARGET  = myprog

BUILD_DIR = ./build
OBJS       = $(patsubst %.c,$(BUILD_DIR)/%.o,$(wildcard *.c))

.PHONY: clean

all: $(BUILD_DIR)/$(TARGET)


$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^


$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)