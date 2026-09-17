CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRCS = binary_parser.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = binary_parser

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o *.o $(TARGET) database_store.vdb

.PHONY: all clean