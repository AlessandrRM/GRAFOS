CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
TARGET = main
OBJS = conectividade.o planaridade.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

conectividade.o: conectividade.c conectividade.h
	$(CC) $(CFLAGS) -c conectividade.c

planaridade.o: planaridade.c planaridade.h conectividade.h
	$(CC) $(CFLAGS) -c planaridade.c

main.o: main.c conectividade.h planaridade.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET) $(TARGET).exe

.PHONY: all clean