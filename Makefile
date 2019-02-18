MAKE = make
GCC = gcc
INCLUDE = include/
SRC = $(wildcard src/*.c)
MOVE = mv
EXC = ./bin/main
LIB = lib/
GIT = git
ADD = add .
COMMIT = commit -m
PUSH = push
READ = @read -p
BIN = bin/*

all :
	$(MAKE) compile -s
	$(MAKE) run -s

compile :
	$(GCC) -I $(INCLUDE) -c $(SRC)
	$(MOVE) *.o $(LIB)
	$(GCC) -o $(EXC) $(LIB)*.o

run :
	$(EXC)

git :
	$(READ) "Enter the message to set up the commit : " message; \
	$(GIT) $(ADD) && $(GIT) $(COMMIT) "$$message" && $(GIT) $(PUSH);

clean :
	rm $(BIN) $(LIB)*
