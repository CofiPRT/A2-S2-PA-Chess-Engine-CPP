CC = g++
CFLAGS = -g -Wall -Wextra -Werror -O3
HEADERS = engine.h functions.h board.h pieces.h utils.h
OBJECTS = main.o engine.o functions.o board.o pieces.o utils.o
EXEC = chess
XEXEC = xboard
XSOURCE = .
XFLAGS = -debug -fd $(XSOURCE) -fcp ./$(EXEC)
XDEBUG = xboard.debug

default: build

build: $(EXEC)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	$(XEXEC) $(XFLAGS) &

run_valgrind: build
	valgrind --dsymutil=yes --track-origins=yes --leak-check=full -q --log-file=v.out ./$(EXEC) < input.txt

clean:
	rm -f $(OBJECTS) $(EXEC) $(XDEBUG)
