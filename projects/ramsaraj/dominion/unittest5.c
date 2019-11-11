#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "customAssert.h"

int main() {

    int k[10] = {adventurer, council_room, feast, mine, baron, tribute, ambassador, minion, great_hall, village};

    struct gameState G; //The gamestate operated on
    struct gameState P; //A "snapshot" of the gamestate before the test, used to compare state
    int choiceInput;
    int success;

    printf("*****Beginning playBaron() Testing*****\n");

    //TEST 1
    printf("~~~Test 1: Player chooses to discard an Estate using a positive-integer input while having 0 coins and an Estate in their hand~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //2 player game:
    initializeGame(2, k, 123, &G);

    //set-up hand and discard pile:
    int playerHand_1[5] = {baron, estate, copper, copper, copper};     //ensure player *does* have an estate in hand
    G.handCount[0] = 5;
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand_1[i];
    }

    G.coins = 0;    //testing when player has 0 coins
    P = G;          //Save state
    choiceInput = (rand() % 10000) + 1;

    playBaron(choiceInput, 0, &G);

    customAssert("numBuys incremented by 1:", G.numBuys == (P.numBuys + 1) );
    customAssert("coins increased by 4:", G.coins == (P.coins + 4) );
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == baron) {
            success = -1;
        }
    }
    customAssert("Baron removed from hand:", success == 0);
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == estate) {
            success = -1;
        }
    }
    customAssert("Estate removed from hand:", success == 0);
    customAssert("Current player's discardCount increased by 2:", G.discardCount[0] == (P.discardCount[0] + 2) );
    customAssert("Estate supply decreased by 1:", G.supplyCount[estate] == (P.supplyCount[estate] - 1) );
    customAssert("Last discard is an Estate:", G.discard[0][G.discardCount[0] - 1] == estate);
    customAssert("Second-to-last discard is a Baron:", G.discard[0][G.discardCount[0] - 2] == baron);



    //TEST 2
    printf("\n~~~Test 2: Player chooses to discard an Estate using a positive-integer input while having 10 coins and an Estate in their hand~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //2 player game:
    initializeGame(2, k, 123, &G);

    //set-up hand and discard pile:
    int playerHand_2[5] = {baron, estate, copper, copper, copper};     //ensure player *does* have an estate in hand
    G.handCount[0] = 5;
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand_2[i];
    }

    G.coins = 10;    //testing when player has 0 coins
    P = G;          //Save state
    choiceInput = (rand() % 10000) + 1;

    playBaron(choiceInput, 0, &G);

    customAssert("numBuys incremented by 1:", G.numBuys == (P.numBuys + 1) );
    customAssert("coins increased by 4:", G.coins == (P.coins + 4) );
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == baron) {
            success = -1;
        }
    }
    customAssert("Baron removed from hand:", success == 0);
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == estate) {
            success = -1;
        }
    }
    customAssert("Estate removed from hand:", success == 0);
    customAssert("Current player's discardCount increased by 2:", G.discardCount[0] == (P.discardCount[0] + 2) );
    customAssert("Estate supply decreased by 1:", G.supplyCount[estate] == (P.supplyCount[estate] - 1) );
    customAssert("Last discard is an Estate:", G.discard[0][G.discardCount[0] - 1] == estate);
    customAssert("Second-to-last discard is a Baron:", G.discard[0][G.discardCount[0] - 2] == baron);



    //TEST 3
    printf("\n~~~Test 3: Player chooses to discard an Estate using a positive-integer input while having 0 coins but no Estate in their hand~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //2 player game:
    initializeGame(2, k, 123, &G);

    //set-up hand and discard pile:
    int playerHand_3[5] = {baron, copper, copper, copper, copper};     //ensure player *does* have an estate in hand
    G.handCount[0] = 5;
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand_3[i];
    }

    G.coins = 0;    //testing when player has 0 coins
    P = G;          //Save state
    choiceInput = (rand() % 10000) + 1;

    playBaron(choiceInput, 0, &G);

    customAssert("numBuys incremented by 1:", G.numBuys == (P.numBuys + 1) );
    customAssert("coins increased by 4:", G.coins == (P.coins + 4) );
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == baron) {
            success = -1;
        }
    }
    customAssert("Baron removed from hand:", success == 0);
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == estate) {
            success = -1;
        }
    }
    customAssert("Estate removed from hand:", success == 0);
    customAssert("Current player's discardCount increased by 2:", G.discardCount[0] == (P.discardCount[0] + 2) );
    customAssert("Estate supply decreased by 1:", G.supplyCount[estate] == (P.supplyCount[estate] - 1) );
    customAssert("Last discard is an Estate:", G.discard[0][G.discardCount[0] - 1] == estate);
    customAssert("Second-to-last discard is a Baron:", G.discard[0][G.discardCount[0] - 2] == baron);


    //TEST 4
    printf("\n~~~Test 4: Player chooses to gain an Estate using a 0 input while having 0 coins and an Estate in their hand~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //2 player game:
    initializeGame(2, k, 123, &G);

    //set-up hand and discard pile:
    int playerHand_4[5] = {baron, estate, copper, copper, copper};     //ensure player *does* have an estate in hand
    G.handCount[0] = 5;
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand_4[i];
    }

    G.coins = 0;    //testing when player has 0 coins
    P = G;          //Save state
    choiceInput = ((rand() % 10000) + 1) * -1;  //ensure that the choice input is negative

    playBaron(choiceInput, 0, &G);

    customAssert("numBuys incremented by 1:", G.numBuys == (P.numBuys + 1) );
    customAssert("coins increased by 4:", G.coins == (P.coins + 4) );
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == baron) {
            success = -1;
        }
    }
    customAssert("Baron removed from hand:", success == 0);
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == estate) {
            success = -1;
        }
    }
    customAssert("Estate removed from hand:", success == 0);
    customAssert("Current player's discardCount increased by 2:", G.discardCount[0] == (P.discardCount[0] + 2) );
    customAssert("Estate supply decreased by 1:", G.supplyCount[estate] == (P.supplyCount[estate] - 1) );
    customAssert("Last discard is an Estate:", G.discard[0][G.discardCount[0] - 1] == estate);
    customAssert("Second-to-last discard is a Baron:", G.discard[0][G.discardCount[0] - 2] == baron);



    //TEST 5
    printf("\n~~~Test 5: Player chooses to discard an Estate using a negative-integer input while having 0 coins and an Estate in their hand~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    //2 player game:
    initializeGame(2, k, 123, &G);

    //set-up hand and discard pile:
    int playerHand_5[5] = {baron, estate, copper, copper, copper};     //ensure player *does* have an estate in hand
    G.handCount[0] = 5;
    for (int i = 0; i < G.handCount[0]; i++) {
        G.hand[0][i] = playerHand_5[i];
    }

    G.coins = 0;    //testing when player has 0 coins
    P = G;          //Save state
    choiceInput = -19;//-((rand() % 10000) + 1);  //ensure that the choice input is negative

    playBaron(choiceInput, 0, &G);

    customAssert("numBuys incremented by 1:", G.numBuys == (P.numBuys + 1) );
    customAssert("coins increased by 4:", G.coins == (P.coins + 4) );
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == baron) {
            success = -1;
        }
    }
    customAssert("Baron removed from hand:", success == 0);
    success = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == estate) {
            success = -1;
        }
    }
    customAssert("Estate removed from hand:", success == 0);
    customAssert("Current player's discardCount increased by 2:", G.discardCount[0] == (P.discardCount[0] + 2) );
    customAssert("Estate supply decreased by 1:", G.supplyCount[estate] == (P.supplyCount[estate] - 1) );
    customAssert("Last discard is an Estate:", G.discard[0][G.discardCount[0] - 1] == estate);
    customAssert("Second-to-last discard is a Baron:", G.discard[0][G.discardCount[0] - 2] == baron);

    return 0;

}

