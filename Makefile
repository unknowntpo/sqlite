CC = gcc
GXX = g++
CFLAGS = -g -Wall
CPPFLAGS = -g -std=c++11
# OBJS = $(wildcard ./src/*.o) 
# OBJS = db.o
SRC = ./src
OBJ = ./obj

TESTBIN = ./bin/test
BIN = ./bin/sqlite
# wildcard should use *
# https://makefiletutorial.com/#-wildcard-1
SRCS = $(wildcard $(SRC)/*.c)

INC_DIR = ./include
INC_FLAGS = $(addprefix -I,$(INC_DIR))

LIB_DIR = ./lib

TEST = ./test
TESTS = $(wildcard $(TEST)/*.c)
TESTOBJS = $(patsubst $(TEST)/%.c, $(OBJ)/%.o, $(TESTS))
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

.PHONY: test/unit
test/unit: $(filter-out $(OBJ)/main.o, $(OBJS)) $(TESTOBJS) $(LIB_DIR)/libgtest.a $(LIB_DIR)/libgtest_main.a
	$(VECHO) '  LD\t $^\n'
	$(Q)$(GXX) $(CPPFLAGS)  -o $(TESTBIN) $^
	@echo ''
	@echo 'Running automated tests...'
	@echo ''
	@$(TESTBIN)

$(OBJ)/%.o: $(TEST)/%.cpp
	$(VECHO) '  CC\t $^\n'
	$(Q)$(GXX) $(CPPFLAGS)  -o $@ $(INC_FLAGS) -c $^

$(OBJ)/%.o: $(SRC)/%.c
	$(VECHO) '  CC\t $^\n'
	$(Q)$(CC) -o $@ $(CFLAGS) $(INC_FLAGS) -c $^

clean:
	@-rm $(BIN) $(OBJS) $(TESTOBJS)