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

all: playdom player 

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1 >> results.out
	echo "\n\n" >> results.out 
	./unittest2 >> results.out
	echo "\n\n" >> results.out
	./unittest3 >> results.out
	echo "\n\n" >> results.out
	./unittest4 >> results.out
	echo "\n\n" >> results.out
	./unittest5 >> results.out
	echo "\n\n" >> results.out
	gcov -b -f dominion.c >> results.out
	echo "\n\n" >> results.out
	cat dominion.c.gcov >> results.out

unittest1: unittest1.o customAssert.o dominion.o rngs.o
	gcc -o unittest1 unittest1.o customAssert.o dominion.o rngs.o -g $(CFLAGS)

unittest2: unittest2.o customAssert.o dominion.o rngs.o
	gcc -o unittest2 unittest2.o customAssert.o dominion.o rngs.o -g $(CFLAGS)

unittest3: unittest3.o customAssert.o dominion.o rngs.o
	gcc -o unittest3 unittest3.o customAssert.o dominion.o rngs.o -g $(CFLAGS)

unittest4: unittest4.o customAssert.o dominion.o rngs.o
	gcc -o unittest4 unittest4.o customAssert.o dominion.o rngs.o -g $(CFLAGS)

unittest5: unittest5.o customAssert.o dominion.o rngs.o
	gcc -o unittest5 unittest5.o customAssert.o dominion.o rngs.o -g $(CFLAGS)

customAssert.o: customAssert.h customAssert.c
	gcc -c customAssert.c -g $(CFLAGS)

unittest1.o:
	gcc -c unittest1.c -g $(CFLAGS)

unittest2.o:
	gcc -c unittest2.c -g $(CFLAGS)

unittest3.o:
	gcc -c unittest3.c -g $(CFLAGS)

unittest4.o:
	gcc -c unittest4.c -g $(CFLAGS)

unittest5.o:
	gcc -c unittest5.c -g $(CFLAGS)

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittest5
