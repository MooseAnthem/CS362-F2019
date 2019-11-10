all:
	gcc -o randomTester testme.c -g -coverage -Wall -std=c99
	./randomTester
	gcov -b -f testme.c

clean:
	rm randomTester