CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -g
TARGET = main
SRCS = main.c agm.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c agm.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) main.exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run