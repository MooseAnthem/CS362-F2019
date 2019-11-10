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

    printf("*****Beginning playMine() Testing*****\n");

    //First test: Valid trade, copper for silver
    printf("~~~Trade Copper for Silver~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    for(int i =0;  i < 4; i++) {
        G.hand[0][i] = estate;
    }
    G.handCount[0] = 5;
    G.hand[0][4] = mine;
    G.hand[0][3] = copper;
    P = G;  //Save state

    success = playMine(0, 4, 3, silver, &G);

    customAssert("Copper traded for Silver allowed:", success == 0);
    customAssert("Player handCount decreased by 1:", G.handCount[0] == (P.handCount[0] - 1) );
    //Check that silver has been added to the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == silver) {
            success = 0;
        }
    }
    customAssert("Silver in hand:", success == 0);
    //Check that the copper has been removed from the player's hand:
    success = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == copper) {
            success = -1;
        }
    }
    customAssert("Copper removed from hand:", success == 0);
    customAssert("Silver removed from supply:", G.supplyCount[silver] == (P.supplyCount[silver] - 1));
    customAssert("Coins unchanged:", P.coins == G.coins);
    customAssert("Actions unchanged:", P.numActions == G.numActions);
    customAssert("NumBuys unchanged:", P.numBuys == G.numBuys);
    customAssert("Player 2's handCount unchanged:", P.handCount[1] == G.handCount[1]);
    customAssert("Player 2's deckCount unchanged:", P.deckCount[1] == G.deckCount[1]);
    customAssert("Player 2's discardCount unchanged:", P.discardCount[1] == G.discardCount[1]);

    //Second test: Invalid trade: Copper for Gold
    //First test: Valid trade, copper for silver
    printf("\n~~~Trade Copper for Gold~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    for(int i =0;  i < 4; i++) {
        G.hand[0][i] = estate;
    }
    G.hand[0][4] = mine;
    G.hand[0][3] = copper;
    G.handCount[0] = 5;
    P = G;  //Save state
    success = playMine(0, 4, 3, gold, &G);

    customAssert("Copper traded for Gold prevented:", success == -1);
    customAssert("Player handCount unchanged:", G.handCount[0] == P.handCount[0]);
    //Check that gold hasn't been added to the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == gold) {
            success = 0;
        }
    }
    customAssert("Gold not in hand:", success == -1);
    //Check that the copper has been removed from the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == copper) {
            success = 0;
        }
    }
    customAssert("Copper kept in hand:", success == 0);
    customAssert("Gold supply unchanged:", G.supplyCount[gold] == P.supplyCount[gold]);
    customAssert("Coins unchanged:", P.coins == G.coins);
    customAssert("Actions unchanged:", P.numActions == G.numActions);
    customAssert("NumBuys unchanged:", P.numBuys == G.numBuys);
    customAssert("Player 2's handCount unchanged:", P.handCount[1] == G.handCount[1]);
    customAssert("Player 2's deckCount unchanged:", P.deckCount[1] == G.deckCount[1]);
    customAssert("Player 2's discardCount unchanged:", P.discardCount[1] == G.discardCount[1]);
    
    
    //Third test: Invalid trade: Silver for Copper
    printf("\n~~~Trade Silver for Copper~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    for(int i =0;  i < 4; i++) {
        G.hand[0][i] = estate;
    }
    G.hand[0][4] = mine;
    G.hand[0][3] = silver;
    G.handCount[0] = 5;
    P = G;  //Save state
    
    success = playMine(0, 4, 3, copper, &G);

    customAssert("Silver traded for Copper prevented:", success == -1);
    customAssert("Player handCount unchanged:", G.handCount[0] == P.handCount[0]);
    //Check that copper was not added to the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == copper) {
            success = 0;
        }
    }
    customAssert("Copper not in hand:", success == -1);
    //Check that the silver has been removed from the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == silver) {
            success = 0;
        }
    }
    customAssert("Silver kept in hand:", success == 0);
    customAssert("Copper supply unchanged:", G.supplyCount[copper] == P.supplyCount[copper]);
    customAssert("Coins unchanged:", P.coins == G.coins);
    customAssert("Actions unchanged:", P.numActions == G.numActions);
    customAssert("NumBuys unchanged:", P.numBuys == G.numBuys);
    customAssert("Player 2's handCount unchanged:", P.handCount[1] == G.handCount[1]);
    customAssert("Player 2's deckCount unchanged:", P.deckCount[1] == G.deckCount[1]);
    customAssert("Player 2's discardCount unchanged:", P.discardCount[1] == G.discardCount[1]);

    //4th test: Invalid trade: Treasure for non-treasure
    printf("\n~~~Trade Copper for Kingdom Card (Village - Cost: 3)~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    for(int i =0;  i < 4; i++) {
        G.hand[0][i] = estate;
    }
    G.hand[0][4] = mine;
    G.hand[0][3] = copper;
    G.handCount[0] = 5;
    P = G;  //Save state
    success = playMine(0, 4, 3, village, &G);

    customAssert("Copper traded for Village prevented:", success == -1);
    customAssert("Player handCount unchanged:", G.handCount[0] == P.handCount[0]);
    //Check that village was not added to the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == village) {
            success = 0;
        }
    }
    customAssert("Village not in hand:", success == -1);
    //Check that the silver has been removed from the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == copper) {
            success = 0;
        }
    }
    customAssert("Copper kept in hand:", success == 0);
    customAssert("Village supply unchanged:", G.supplyCount[village] == P.supplyCount[village]);
    customAssert("Coins unchanged:", P.coins == G.coins);
    customAssert("Actions unchanged:", P.numActions == G.numActions);
    customAssert("NumBuys unchanged:", P.numBuys == G.numBuys);
    customAssert("Player 2's handCount unchanged:", P.handCount[1] == G.handCount[1]);
    customAssert("Player 2's deckCount unchanged:", P.deckCount[1] == G.deckCount[1]);
    customAssert("Player 2's discardCount unchanged:", P.discardCount[1] == G.discardCount[1]);

    //5th test: Invalid trade: Treasure for non-treasure
    printf("\n~~~Trade Copper for Kingdom Card (Tribute - Cost: 5)~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    for(int i =0;  i < 4; i++) {
        G.hand[0][i] = estate;
    }
    G.hand[0][4] = mine;
    G.hand[0][3] = copper;
    G.handCount[0] = 5;
    P = G;  //Save state
    success = playMine(0, 4, 3, tribute, &G);

    customAssert("Copper traded for Tribute prevented:", success == -1);
    customAssert("Player handCount unchanged:", G.handCount[0] == P.handCount[0]);
    //Check that tribute was not added to the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == tribute) {
            success = 0;
        }
    }
    customAssert("Tribute not in hand:", success == -1);
    //Check that the copper has been removed from the player's hand:
    success = -1;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == copper) {
            success = 0;
        }
    }
    customAssert("Copper kept in hand:", success == 0);
    customAssert("Tribute supply unchanged:", G.supplyCount[tribute] == P.supplyCount[tribute]);
    customAssert("Coins unchanged:", P.coins == G.coins);
    customAssert("Actions unchanged:", P.numActions == G.numActions);
    customAssert("NumBuys unchanged:", P.numBuys == G.numBuys);
    customAssert("Player 2's handCount unchanged:", P.handCount[1] == G.handCount[1]);
    customAssert("Player 2's deckCount unchanged:", P.deckCount[1] == G.deckCount[1]);
    customAssert("Player 2's discardCount unchanged:", P.discardCount[1] == G.discardCount[1]);

    return 0;
}