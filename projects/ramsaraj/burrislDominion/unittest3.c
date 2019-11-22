#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "customAssert.h"

int main() {

    int k[10] = {adventurer, council_room, feast, mine, baron, tribute, ambassador, minion, great_hall, village};

    struct gameState G; //The gamestate operated on
    struct gameState P; //A "snapshot" of the gamestate before the test, used to compare state
    int success;

    int currentPlayer = 0;
    int ambassadorPos;
    int cardToDiscardPos;
    int quantityToDiscard;


    printf("*****Beginning playAmbassador() Testing*****\n");


    printf("~~~Test 1: Valid 2 Copy discard~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(4, k, 123, &G);

    //Setup hands:
    for (int i = 0; i < 5; i++) {
        G.discard[1][i] = G.discard[2][i] = G.discard[3][i] = copper;
    }
    G.discardCount[1] = G.discardCount[2] = G.discardCount[3] = 5;

    int mainHand_1[5] = {ambassador, gold, gold, gold, copper};
    for (int i = 0; i < 5; i ++) {
        G.hand[0][i] = mainHand_1[i];
    }
    G.handCount[0] = 5;
    
    //save State:
    P = G;

    ambassadorPos = 0;
    cardToDiscardPos = 1;
    quantityToDiscard = 2;
    success = doAmbassador(currentPlayer, cardToDiscardPos, quantityToDiscard, &G, ambassadorPos);

    customAssert("Play allowed:", success == 0);
    customAssert("Handcount decreased by `1 + quantityToDiscard`", G.handCount[0] == (P.handCount[0] - (1 + quantityToDiscard)));
    success = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == ambassador){
            success = -1;
        }
    }
    customAssert("Ambassador discarded from hand:", success == 0);
    printf("Checking other player discountCounts:\n");
        customAssert("\tPlayer 1 discardCount increased by 1:", G.discardCount[1] == (P.discardCount[1] + 1));
        customAssert("\tPlayer 2 discardCount increased by 1:", G.discardCount[2] == (P.discardCount[2] + 1));
        customAssert("\tPlayer 3 discardCount increased by 1:", G.discardCount[3] == (P.discardCount[3] + 1));
    printf("Checking if top cards in discard matches `cardToDiscard`\n");
        customAssert("\tPlayer 1 top card equals `cardToDiscard`:", G.discard[1][G.discardCount[1]] == gold);
        customAssert("\tPlayer 2 top card equals `cardToDiscard`:", G.discard[2][G.discardCount[2]] == gold);
        customAssert("\tPlayer 3 top card equals `cardToDiscard`:", G.discard[3][G.discardCount[3]] == gold);
    customAssert("Supply count of cardToDiscard decreased by `(numPlayers - 1) + qauntityToDiscard'", G.supplyCount[gold] == (P.supplyCount[gold] - 3 + quantityToDiscard));
    printf("Checking if game state unchanged:\n");
        customAssert("\tcoins unchanged:", G.coins == P.coins);
        customAssert("\tnumBuys unchanged:", G.numBuys == P.numBuys);
        customAssert("\tnumActions unchanged:", G.numActions == P.numActions);

    
    
    
    
    
    printf("\n\n~~~Test 2: Invalid 2 Copy discard~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(4, k, 123, &G);

    //Setup hands:
    for (int i = 0; i < 5; i++) {
        G.discard[1][i] = G.discard[2][i] = G.discard[3][i] = copper;
    }
    G.discardCount[1] = G.discardCount[2] = G.discardCount[3] = 5;

    int mainHand_2[5] = {ambassador, gold, treasure_map, treasure_map, treasure_map};
    for (int i = 0; i < 5; i ++) {
        G.hand[0][i] = mainHand_2[i];
    }
    G.handCount[0] = 5;
    
    //save State:
    P = G;

    ambassadorPos = 0;
    cardToDiscardPos = 1;
    quantityToDiscard = 2;
    success = doAmbassador(currentPlayer, cardToDiscardPos, quantityToDiscard, &G, ambassadorPos);

    customAssert("Play allowed:", success == 0);
    customAssert("Handcount decreased by `1 + quantityToDiscard`", G.handCount[0] == (P.handCount[0] - (1 + quantityToDiscard)));
    success = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == ambassador){
            success = -1;
        }
    }
    customAssert("Ambassador discarded from hand:", success == 0);
    printf("Checking other player discountCounts:\n");
        customAssert("\tPlayer 1 discardCount increased by 1:", G.discardCount[1] == (P.discardCount[1] + 1));
        customAssert("\tPlayer 2 discardCount increased by 1:", G.discardCount[2] == (P.discardCount[2] + 1));
        customAssert("\tPlayer 3 discardCount increased by 1:", G.discardCount[3] == (P.discardCount[3] + 1));
    printf("Checking if top cards in discard matches `cardToDiscard`:\n");
        customAssert("\tPlayer 1 top card equals `cardToDiscard`:", G.discard[1][G.discardCount[1]] == gold);
        customAssert("\tPlayer 2 top card equals `cardToDiscard`:", G.discard[2][G.discardCount[2]] == gold);
        customAssert("\tPlayer 3 top card equals `cardToDiscard`:", G.discard[3][G.discardCount[3]] == gold);
    customAssert("Supply count of cardToDiscard decreased by `(numPlayers - 1) + qauntityToDiscard'", G.supplyCount[gold] == (P.supplyCount[gold] - 3 + quantityToDiscard));
    printf("Checking if game state unchanged:\n");
        customAssert("\tcoins unchanged:", G.coins == P.coins);
        customAssert("\tnumBuys unchanged:", G.numBuys == P.numBuys);
        customAssert("\tnumActions unchanged:", G.numActions == P.numActions);


    
    
    
    
    
    printf("\n\n~~~Test 3: Invalid attempt to discard played Ambassador card~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(4, k, 123, &G);

    //Setup hands:
    for (int i = 0; i < 5; i++) {
        G.discard[1][i] = G.discard[2][i] = G.discard[3][i] = copper;
    }
    G.discardCount[1] = G.discardCount[2] = G.discardCount[3] = 5;

    int mainHand_3[5] = {ambassador, ambassador, ambassador, copper, copper};
    for (int i = 0; i < 5; i ++) {
        G.hand[0][i] = mainHand_3[i];
    }
    G.handCount[0] = 5;
    
    //save State:
    P = G;

    ambassadorPos = 0;
    cardToDiscardPos = 0;
    quantityToDiscard = 2;
    success = doAmbassador(currentPlayer, cardToDiscardPos, quantityToDiscard, &G, ambassadorPos);

    customAssert("Play allowed:", success == 0);
    customAssert("Handcount decreased by `1 + quantityToDiscard`", G.handCount[0] == (P.handCount[0] - (1 + quantityToDiscard)));
    success = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == ambassador){
            success = -1;
        }
    }
    customAssert("Ambassador discarded from hand:", success == 0);
    printf("Checking other player discountCounts:\n");
        customAssert("\tPlayer 1 discardCount increased by 1:", G.discardCount[1] == (P.discardCount[1] + 1));
        customAssert("\tPlayer 2 discardCount increased by 1:", G.discardCount[2] == (P.discardCount[2] + 1));
        customAssert("\tPlayer 3 discardCount increased by 1:", G.discardCount[3] == (P.discardCount[3] + 1));
    printf("Checking if top cards in discard matches `cardToDiscard`\n");
        customAssert("\tPlayer 1 top card equals `cardToDiscard`:", G.discard[1][G.discardCount[1]] == ambassador);
        customAssert("\tPlayer 2 top card equals `cardToDiscard`:", G.discard[2][G.discardCount[2]] == ambassador);
        customAssert("\tPlayer 3 top card equals `cardToDiscard`:", G.discard[3][G.discardCount[3]] == ambassador);
    customAssert("Supply count of cardToDiscard decreased by `(numPlayers - 1) + qauntityToDiscard'", G.supplyCount[gold] == (P.supplyCount[gold] - 3 + quantityToDiscard));
    printf("Checking if game state unchanged:\n");
        customAssert("\tcoins unchanged:", G.coins == P.coins);
        customAssert("\tnumBuys unchanged:", G.numBuys == P.numBuys);
        customAssert("\tnumActions unchanged:", G.numActions == P.numActions);
    




    printf("\n\n~~~Test 4: Valid attempt to discard 1 copy~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(4, k, 123, &G);

    //Setup hands:
    for (int i = 0; i < 5; i++) {
        G.discard[1][i] = G.discard[2][i] = G.discard[3][i] = copper;
    }
    G.discardCount[1] = G.discardCount[2] = G.discardCount[3] = 5;

    int mainHand_4[5] = {ambassador, gold, gold, copper, copper};
    for (int i = 0; i < 5; i ++) {
        G.hand[0][i] = mainHand_4[i];
    }
    G.handCount[0] = 5;
    
    //save State:
    P = G;

    ambassadorPos = 0;
    cardToDiscardPos = 1;
    quantityToDiscard = 1;
    success = doAmbassador(currentPlayer, cardToDiscardPos, quantityToDiscard, &G, ambassadorPos);

    customAssert("Play allowed:", success == 0);
    customAssert("Handcount decreased by `1 + quantityToDiscard`", G.handCount[0] == (P.handCount[0] - (1 + quantityToDiscard)));
    success = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == ambassador){
            success = -1;
        }
    }
    customAssert("Ambassador discarded from hand:", success == 0);
    printf("Checking other player discountCounts:\n");
        customAssert("\tPlayer 1 discardCount increased by 1:", G.discardCount[1] == (P.discardCount[1] + 1));
        customAssert("\tPlayer 2 discardCount increased by 1:", G.discardCount[2] == (P.discardCount[2] + 1));
        customAssert("\tPlayer 3 discardCount increased by 1:", G.discardCount[3] == (P.discardCount[3] + 1));
    printf("Checking if top cards in discard matches `cardToDiscard`\n");
        customAssert("\tPlayer 1 top card equals `cardToDiscard`:", G.discard[1][G.discardCount[1]] == gold);
        customAssert("\tPlayer 2 top card equals `cardToDiscard`:", G.discard[2][G.discardCount[2]] == gold);
        customAssert("\tPlayer 3 top card equals `cardToDiscard`:", G.discard[3][G.discardCount[3]] == gold);
    customAssert("Supply count of cardToDiscard decreased by `(numPlayers - 1) + qauntityToDiscard'", G.supplyCount[gold] == (P.supplyCount[gold] - 3 + quantityToDiscard));
    printf("Checking if game state unchanged:\n");
        customAssert("\tcoins unchanged:", G.coins == P.coins);
        customAssert("\tnumBuys unchanged:", G.numBuys == P.numBuys);
        customAssert("\tnumActions unchanged:", G.numActions == P.numActions);
    
    return 0;
}