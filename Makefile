
CC = gcc
CFLAGS = -g -Wall
TARGET = db

all: $(TARGET)

$(TARGET): db.c db.h
	$(CC) -o $@ $(CFLAGS)  $< 

.PHONY: clean
clean:
	-rm -rf $(TARGET)