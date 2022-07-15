CC = gcc
CFLAGS = -g -Wall
# OBJS = $(wildcard ./src/*.o) 
# OBJS = db.o
SRC = ./src
OBJ = ./obj
BIN = ./bin/sqlite
# wildcard should use *
# https://makefiletutorial.com/#-wildcard-1
SRCS = $(wildcard $(SRC)/*.c)
# >>?
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

ifeq ("$(VERBOSE)", "1")
	Q :=
	VECHO = @true
else
	Q := @
	VECHO = @printf
endif

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(VECHO) '  LD\t $^\n'
	$(Q)$(CC) -o $@ $^

test/it:
	@bundle exec rspec

test/unit: db_test.o db.o
	$(VECHO) '  LD\t $^\n'
	$(Q)$(CC) -o $@ $^
	@echo ''
	@echo 'Running automated tests...'
	@echo ''
	@./$@

$(OBJ)/%.o: $(SRC)/%.c
	$(VECHO) '  CC\t $^\n'
	$(Q)$(CC) -o $@ $(CFLAGS) -c $^

clean:
	@-rm $(BIN) $(OBJS)