# @file Makefile
# Makefile for process_flare_data

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Executable name
TARGET = process_flare_data

# Source files
SRCS = process_flare_data.c fraction.c
HDRS = fraction.h

# Default target
all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Clean up build files
clean:
	rm -f $(TARGET)
