PROG=snake
FILES=src/main.c src/snake.c
FLAGS=-Wall -Wextra -pedantic -lSDL2

build:
	gcc -o $(PROG) $(FILES) $(FLAGS)

run:
	./$(PROG)
