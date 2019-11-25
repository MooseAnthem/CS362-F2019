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

unittest1: unittest1.c dominion.o player
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o player
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o player
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o player
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

unittest5: unittest5.c dominion.o player
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)

unittest6: unittest6.c dominion.o player
	gcc -o unittest6 -g unittest6.c dominion.o rngs.o $(CFLAGS)

unittest7: unittest7.c dominion.o player
	gcc -o unittest7 -g unittest7.c dominion.o rngs.o $(CFLAGS)

unittest8: unittest8.c dominion.o player
	gcc -o unittest8 -g unittest8.c dominion.o rngs.o $(CFLAGS)

unittest9: unittest9.c dominion.o player
	gcc -o unittest9 -g unittest9.c dominion.o rngs.o $(CFLAGS)

unittest10: unittest10.c dominion.o player
	gcc -o unittest10 -g unittest10.c dominion.o rngs.o $(CFLAGS)

unittest11: unittest11.c dominion.o player
	gcc -o unittest11 -g unittest11.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5 unittest6 unittest7 unittest8 unittest9 unittest10 unittest11

##	echo "unittest2.c results:" >> randomtestresults.out
##	$(MAKE) --no - print - directory unittest1
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	./unittest6 >> unittestresults.out
	./unittest7 >> unittestresults.out
	./unittest8 >> unittestresults.out
	./unittest9 >> unittestresults.out
	./unittest10 >> unittestresults.out
	./unittest11 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player unittestresults

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittest5 unittest6 unittest7 unittest8 unittest9 unittest10 unittest11 unittestresults


