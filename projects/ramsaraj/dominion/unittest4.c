#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "customAssert.h"

int main() {

    int k[10] = {adventurer, council_room, feast, mine, baron, tribute, ambassador, minion, great_hall, village};

    struct gameState G; //The gamestate operated on
    struct gameState P; //A "snapshot" of the gamestate before the test, used to compare state
    int success;

    int currentPlayer = 0;
    int minionCardPos = 0;


    printf("*****Beginning playMinion() Testing*****\n");

    //TEST 1
    printf("~~~Test 1: Player 0 chooses to gain gold~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //3 player game:
    initializeGame(3, k, 123, &G);

    //hand setup:
    for(int i = 0; i < 10; i++) {
        G.hand[0][i] = G.hand[1][i] = copper;
        if (i < 3) {
            G.hand[2][i] = copper;
        }
    }
    G.handCount[0] = G.handCount[1] = 10;
    G.handCount[2] = 3;
    //Give the current player a minion card:
    G.hand[0][0] = minion;

    //each player has a 5 cards in their discard pile:
    G.discardCount[0] = G.discardCount[1] = G.discardCount[2] = 5;
    for (int i = 0; i < 5; i++) {
        G.discard[0][i] = G.discard[1][i] = G.discard[2][i] = estate;
    }

    P = G; // save game state

    playMinion(minionCardPos, currentPlayer, 1, 0, &G);

    customAssert("numActions incremented:", G.numActions == (P.numActions + 1) );
    customAssert("coins increased by 2:", G.coins == (P.coins + 2) );
    success = 0;
    for (int i = 0; i < G.handCount[currentPlayer]; i++) {
        if (G.hand[currentPlayer][i] == minion) {
            success = -1;
        }
    }
    customAssert("Minion card removed from current player's hand:", success == 0);
    printf("Current player's hand info:\n");
        customAssert("\tCurrent player's hand is size 9:", G.handCount[currentPlayer] == 9);
        customAssert("\tCurrent player's hand is size 4:", G.handCount[currentPlayer] == 4);
    printf("Second player's hand info:\n");
        customAssert("\tSecond player's hand is still size 10:", G.handCount[1] == 10);
        customAssert("\tSecond player's hand is size 4:", G.handCount[1] == 4);
    printf("Third player's hand info:\n");
        customAssert("\tThird player's hand is still size 3:", G.handCount[2] == 3);
        customAssert("\tThird player's hand is size 4:", G.handCount[2] == 4);



    //TEST 2
    printf("\n~~~Test 2: Player 0 chooses to force discard and redraw~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //3 player game:
    initializeGame(3, k, 123, &G);

    //hand setup:
    for(int i = 0; i < 10; i++) {
        G.hand[0][i] = G.hand[1][i] = copper;
        if (i < 3) {
            G.hand[2][i] = copper;
        }
    }
    G.handCount[0] = G.handCount[1] = 10;
    G.handCount[2] = 3;
    //Give the current player a minion card:
    G.hand[0][0] = minion;

    //each player has a 5 cards in their discard pile:
    G.discardCount[0] = G.discardCount[1] = G.discardCount[2] = 5;
    for (int i = 0; i < 5; i++) {
        G.discard[0][i] = G.discard[1][i] = G.discard[2][i] = estate;
    }

    P = G; // save game state

    playMinion(minionCardPos, currentPlayer, 0, 1, &G);

    customAssert("numActions incremented:", G.numActions == (P.numActions + 1) );
    customAssert("coins increased by 2:", G.coins == (P.coins + 2) );
    success = 0;
    for (int i = 0; i < G.handCount[currentPlayer]; i++) {
        if (G.hand[currentPlayer][i] == minion) {
            success = -1;
        }
    }
    customAssert("Minion card removed from current player's hand:", success == 0);
    printf("Current player's hand info:\n");
        customAssert("\tCurrent player's hand is size 9:", G.handCount[currentPlayer] == 9);
        customAssert("\tCurrent player's hand is size 4:", G.handCount[currentPlayer] == 4);
    printf("Second player's hand info:\n");
        customAssert("\tSecond player's hand is still size 10:", G.handCount[1] == 10);
        customAssert("\tSecond player's hand is size 4:", G.handCount[1] == 4);
    printf("Third player's hand info:\n");
        customAssert("\tThird player's hand is still size 3:", G.handCount[2] == 3);
        customAssert("\tThird player's hand is size 4:", G.handCount[2] == 4);



    //TEST 3
    printf("\n~~~Test 3: Player 0 chooses neither action~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //3 player game:
    initializeGame(3, k, 123, &G);

    //hand setup:
    for(int i = 0; i < 10; i++) {
        G.hand[0][i] = G.hand[1][i] = copper;
        if (i < 3) {
            G.hand[2][i] = copper;
        }
    }
    G.handCount[0] = G.handCount[1] = 10;
    G.handCount[2] = 3;
    //Give the current player a minion card:
    G.hand[0][0] = minion;

    //each player has a 5 cards in their discard pile:
    G.discardCount[0] = G.discardCount[1] = G.discardCount[2] = 5;
    for (int i = 0; i < 5; i++) {
        G.discard[0][i] = G.discard[1][i] = G.discard[2][i] = estate;
    }

    P = G; // save game state

    playMinion(minionCardPos, currentPlayer, 0, 0, &G);

    customAssert("numActions incremented:", G.numActions == (P.numActions + 1) );
    customAssert("coins increased by 2:", G.coins == (P.coins + 2) );
    success = 0;
    for (int i = 0; i < G.handCount[currentPlayer]; i++) {
        if (G.hand[currentPlayer][i] == minion) {
            success = -1;
        }
    }
    customAssert("Minion card removed from current player's hand:", success == 0);
    printf("Current player's hand info:\n");
        customAssert("\tCurrent player's hand is size 9:", G.handCount[currentPlayer] == 9);
        customAssert("\tCurrent player's hand is size 4:", G.handCount[currentPlayer] == 4);
    printf("Second player's hand info:\n");
        customAssert("\tSecond player's hand is still size 10:", G.handCount[1] == 10);
        customAssert("\tSecond player's hand is size 4:", G.handCount[1] == 4);
    printf("Third player's hand info:\n");
        customAssert("\tThird player's hand is still size 3:", G.handCount[2] == 3);
        customAssert("\tThird player's hand is size 4:", G.handCount[2] == 4);



    //TEST 4
    printf("\n~~~Test 4: Player 0 chooses neither action~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //3 player game:
    initializeGame(3, k, 123, &G);

    //hand setup:
    for(int i = 0; i < 10; i++) {
        G.hand[0][i] = G.hand[1][i] = copper;
        if (i < 3) {
            G.hand[2][i] = copper;
        }
    }
    G.handCount[0] = G.handCount[1] = 10;
    G.handCount[2] = 3;
    //Give the current player a minion card:
    G.hand[0][0] = minion;

    //each player has a 5 cards in their discard pile:
    G.discardCount[0] = G.discardCount[1] = G.discardCount[2] = 5;
    for (int i = 0; i < 5; i++) {
        G.discard[0][i] = G.discard[1][i] = G.discard[2][i] = estate;
    }

    P = G; // save game state

    playMinion(minionCardPos, currentPlayer, 1, 1, &G);

    customAssert("numActions incremented:", G.numActions == (P.numActions + 1) );
    customAssert("coins increased by 2:", G.coins == (P.coins + 2) );
    success = 0;
    for (int i = 0; i < G.handCount[currentPlayer]; i++) {
        if (G.hand[currentPlayer][i] == minion) {
            success = -1;
        }
    }
    customAssert("Minion card removed from current player's hand:", success == 0);
    printf("Current player's hand info:\n");
        customAssert("\tCurrent player's hand is size 9:", G.handCount[currentPlayer] == 9);
        customAssert("\tCurrent player's hand is size 4:", G.handCount[currentPlayer] == 4);
    printf("Second player's hand info:\n");
        customAssert("\tSecond player's hand is still size 10:", G.handCount[1] == 10);
        customAssert("\tSecond player's hand is size 4:", G.handCount[1] == 4);
    printf("Third player's hand info:\n");
        customAssert("\tThird player's hand is still size 3:", G.handCount[2] == 3);
        customAssert("\tThird player's hand is size 4:", G.handCount[2] == 4);
    
    return 0;

}