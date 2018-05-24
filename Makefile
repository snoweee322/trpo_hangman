all: program

program: build/main.o build/game.o build/hangman.o bin
	gcc -Wall -Werror build/main.o build/game.o build/hangman.o -o bin/program

build/main.o: source/main.c build
	gcc -Wall -Werror -c source/main.c -o build/main.o

build/game.o: source/game.c
	gcc -Wall -Werror -c source/game.c -o build/game.o

build/hangman.o: source/hangman.c
	gcc -Wall -Werror -c source/hangman.c -o build/hangman.o

build:
	mkdir build

bin:
	mkdir bin

.PHONY: clean

clean:
	rm -rf bin/program build/*.o

