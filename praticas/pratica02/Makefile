CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
TARGET = main
OBJS = busca_largura.o busca_profundidade.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

busca_largura.o: busca_largura.c busca_largura.h
	$(CC) $(CFLAGS) -c busca_largura.c

busca_profundidade.o: busca_profundidade.c busca_profundidade.h busca_largura.h
	$(CC) $(CFLAGS) -c busca_profundidade.c

main.o: main.c busca_largura.h busca_profundidade.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET) $(TARGET).exe

.PHONY: all clean