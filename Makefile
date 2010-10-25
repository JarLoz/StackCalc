# Makefile for stackcalc
CC = gcc -ansi -pedantic -Wall -Wextra -g -DTESTMODE

stackcalc: Main.o stackCalculator.o stack.o postfixArray.o
	$(CC) -lm -o stackcalc Main.o stackCalculator.o stack.o postfixArray.o
	mv *.o src/
Main.o: src/Main.c
	$(CC) -c src/Main.c
stackCalculator.o: src/stackCalculator.c
	$(CC) -c src/stackCalculator.c
stack.o: src/stack.c
	$(CC) -c src/stack.c
postfixArray.o: src/postfixArray.c
	$(CC) -c src/postfixArray.c
clean:
	rm src/*.o && rm stackcalc
