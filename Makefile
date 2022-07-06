CC = gcc
CFLAGS = -g -Wall
# OBJS = $(wildcard ./src/*.o) 
OBJS = db.o
SRCS = $(wildcard ./src/*.c)

ifeq ("$(VERBOSE)", "1")
	Q :=
	VECHO = @true
else
	Q := @
	VECHO = @printf
endif

all: db

db: $(OBJS)
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

$(OBJS): $(SRCS)
	$(VECHO) '  CC\t $^\n'
	$(Q)$(CC) -o $@ $(CFLAGS) -c $^

clean:
	@-rm test db $(OBJS)