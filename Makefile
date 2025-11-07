CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Iinclude
SRC = $(wildcard src/*.c)
TARGET = gram

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) 
run:
	./$(TARGET)
clean:
	rm -f $(TARGET)