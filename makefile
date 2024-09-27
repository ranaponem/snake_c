PROG=snake
FILES=main.c
FLAGS=-Wall -Wextra -pedantic -lSDL2

build:
	gcc -o $(PROG) $(FILES) $(FLAGS)

run:
	./$(PROG)
