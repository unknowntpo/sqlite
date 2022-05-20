
CC = gcc
CFLAGS = -g -Wall
TARGET = db

all: $(TARGET)

$(TARGET): db.c db.h
	$(CC) -o $@ $(CFLAGS)  $< 

test:
	@bundle exec rspec

.PHONY: test clean
clean:
	-rm -rf $(TARGET)
