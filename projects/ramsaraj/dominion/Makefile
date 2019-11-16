CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard1: randomtestcard1.c 
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c -g $(CFLAGS)

randomtestcard2: randomtestcard2.c 
	gcc -o randomtestcard2 randomtestcard2.c dominion.c rngs.c -g $(CFLAGS)

randomtestcard3: randomtestcard3.c 
	gcc -o randomtestcard3 randomtestcard3.c dominion.c rngs.c -g $(CFLAGS)

randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
	./randomtestcard1 100 >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out *.gcno *.gcda *.gcov testDrawCard testDrawCard.exe randomtestcard1 randomtestcard2 randomtestcard3
