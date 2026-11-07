CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
TARGET = main
OBJS = coloracao.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

coloracao.o: coloracao.c coloracao.h
	$(CC) $(CFLAGS) -c coloracao.c

main.o: main.c coloracao.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET) $(TARGET).exe

.PHONY: all clean