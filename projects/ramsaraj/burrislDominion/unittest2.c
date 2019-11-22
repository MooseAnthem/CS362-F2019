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
    int tributeRevealedCards[2] = {-1, -1};
    int found;

    printf("*****Beginning playTribute() Testing*****\n");

    printf("~~~First Test: Player 1 has full deck, reveals 2 unique treasure cards~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    int player0Hand_1[5] = {estate, estate, estate, estate, tribute};
    int player1Deck_1[5] = {adventurer, adventurer, adventurer, copper, silver};
    for(int i =0;  i < 5; i++) {
        G.hand[0][i] = player0Hand_1[i];
        G.deck[1][i] = player1Deck_1[i];
    }
    G.handCount[0] = G.deckCount[1] = 5;
    tributeRevealedCards[0] = tributeRevealedCards [1] = -1;
    P = G;  //save state

    doTribute(0, 1, tributeRevealedCards, 0, 0, &G, 0);
    

    customAssert("coins incremented correctly (+4):",           G.coins == (P.coins + 4));
    customAssert("numBuys unchanged:",                          G.numBuys == P.numBuys);
    customAssert("numActions unchanged:",                       G.numActions == P.numActions);
    found = 0;
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == tribute) {
            found = 1;
        }
    }
    customAssert("Player 0 discarded Tribute:",                 found == 0);
    customAssert("Player 0 handcount unchanged:",               G.handCount[0] == P.handCount[0]);
    customAssert("Player 1 deck decremented correctly (-2):",   (G.deckCount[1] - 2) == P.deckCount[1]);
    customAssert("Player 1 discarded 2 cards:",                 G.discard[1] == (P.discard[1] + 2) );
    customAssert("Player 1 discarded Copper and Silver:",       ( G.discard[1][0] == copper && G.discard[1][1] == silver ) );
    customAssert("Player 1 revealed cards set to -1 in deck:",  ( G.deck[1][3] == -1 && G.deck[1][4] == -1) );
    customAssert("Player 1 handCount unchanged:",               P.handCount[1] == G.handCount[1]);


    printf("\n~~~Second Test: Player 1 has full deck, reveals duplicate treasure cards~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    int player0Hand_2[5] = {estate, estate, estate, estate, tribute};
    int player1Deck_2[5] = {copper, copper, copper, copper, copper};
    for(int i =0;  i < 5; i++) {
        G.hand[0][i] = player0Hand_2[i];
        G.deck[1][i] = player1Deck_2[i];
    }
    G.handCount[0] = G.deckCount[1] = 5;
    tributeRevealedCards[0] = tributeRevealedCards [1] = -1;
    P = G;  //save state
    
    doTribute(0, 1, tributeRevealedCards, 0, 0, &G, 0);

    customAssert("coins incremented correctly (+2):",           G.coins == (P.coins + 2));
    customAssert("numBuys unchanged:",                          G.numBuys == P.numBuys);
    customAssert("numActions unchanged:",                       G.numActions == P.numActions);
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == tribute) {
            found = 1;
        }
    }
    customAssert("Player 0 discarded Tribute:",                 found == 0);
    customAssert("Player 0 handcount unchanged:",               G.handCount[0] == P.handCount[0]);
    customAssert("Player 1 deck decremented correctly (-2):",   (G.deckCount[1] - 2) == P.deckCount[1]);
    customAssert("Player 1 discarded 2 cards:",                 G.discard[1] == (P.discard[1] + 2) );
    customAssert("Player 1 discarded Estate and Estate:",       ( G.discard[1][0] == province && G.discard[1][1] == estate ) );
    customAssert("Player 1 revealed cards set to -1 in deck:",  ( G.deck[1][3] == -1 && G.deck[1][4] == -1) );
    customAssert("Player 1 handCount unchanged:",               P.handCount[1] == G.handCount[1]);
    

    printf("\n~~~Third Test: Player 1 has empty deck, and empty discard pile~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    int player0Hand_3[5] = {estate, estate, estate, estate, tribute};
    for(int i =0;  i < 5; i++) {
        G.hand[0][i] = player0Hand_3[i];
    }
    G.handCount[0] = 5;
    G.deckCount[1] = G.discardCount[1] = 0;
    tributeRevealedCards[0] = tributeRevealedCards [1] = -1;
    P = G;  //save state
    
    doTribute(0, 1, tributeRevealedCards, 0, 0, &G, 0);

    customAssert("coins unchanged:",                            G.coins == P.coins);
    customAssert("numBuys unchanged:",                          G.numBuys == P.numBuys);
    customAssert("numActions unchanged:",                       G.numActions == P.numActions);
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == tribute) {
            found = 1;
        }
    }
    customAssert("Player 0 discarded Tribute:",                 found == 0);
    customAssert("Player 0 handcount unchanged:",               G.handCount[0] == P.handCount[0]);
    customAssert("Player 1 deckCount unchanged:",               G.deckCount[1] == P.deckCount[1]);
    customAssert("Player 1 discardCount unchanged:",            G.discardCount[1] == P.discardCount[1]);
    customAssert("Player 1 handCount unchanged:",               P.handCount[1] == G.handCount[1]);


    printf("\n~~~Fourth Test: Player 1 has empty deck, but discard pile > 2~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    int player0Hand_4[5] = {estate, estate, estate, estate, tribute};
    int player1Discard_4[5] = {copper, copper, copper, copper, copper};
    for(int i =0;  i < 5; i++) {
        G.hand[0][i] = player0Hand_4[i];
        G.discard[1][i] = player1Discard_4[i];
    }
    G.handCount[0] = G.discardCount[1] = 5;
    G.deckCount[1] = 0;
    tributeRevealedCards[0] = tributeRevealedCards [1] = -1;
    P = G;  //save state
    
    doTribute(0, 1, tributeRevealedCards, 0, 0, &G, 0);

    customAssert("coins incremented correctly:",                G.coins == (P.coins + 2) );
    customAssert("numBuys unchanged:",                          G.numBuys == P.numBuys);
    customAssert("numActions unchanged:",                       G.numActions == P.numActions);
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == tribute) {
            found = 1;
        }
    }
    customAssert("Player 0 discarded Tribute:",                 found == 0);
    customAssert("Player 0 handcount unchanged:",               G.handCount[0] == P.handCount[0]);
    customAssert("Player 1 deckCount unchanged:",               G.deckCount[1] == P.deckCount[1]);
    customAssert("Player 1 discardCount now 0:",                G.discardCount[1] == 0);
    customAssert("Player 1 handCount unchanged:",               P.handCount[1] == G.handCount[1]);

    //Fifth test: Next Player only has 1 card in their discard pile.
    printf("\n~~~Fifth Test: Next player has empty deck, and only 1 card in discard~~~\n");
    memset(&G, 0, sizeof(struct gameState));
    initializeGame(2, k, 123, &G);
    int player0Hand_5[5] = {estate, estate, estate, estate, tribute};
    int player1Discard_5[5] = {estate};
    for(int i =0;  i < 5; i++) {
        G.hand[0][i] = player0Hand_5[i];
        G.discard[1][i] = player1Discard_5[i];
    }
    G.handCount[0] = 5;
    G.deckCount[1] = 0;
    G.discardCount[1] = 1;
    tributeRevealedCards[0] = tributeRevealedCards [1] = -1;
    P = G;  //save state
    printf("1 Handcount: %d\n", G.handCount[0]);
    doTribute(0, 1, tributeRevealedCards, 0, 0, &G, 0);
    printf("1 Handcount: %d\n", G.handCount[0]);

    customAssert("coins unchanged:",                            G.coins == P.coins);
    customAssert("numBuys unchanged:",                          G.numBuys == P.numBuys);
    customAssert("numActions unchanged:",                       G.numActions == P.numActions);
    for (int i = 0; i < G.handCount[0]; i++) {
        if (G.hand[0][i] == tribute) {
            found = 1;
        }
    }
    customAssert("Player 0 discarded Tribute:",                 found == 0);
    customAssert("Player 0 handcount increased by 2:",          G.handCount[0] == (P.handCount[0] + 2));
    customAssert("Player 1 deckCount unchanged:",               G.deckCount[1] == P.deckCount[1]);
    customAssert("Player 1 discardCount unchanged:",            G.discardCount[1] == P.discardCount[1]);
    customAssert("Player 1 handCount unchanged:",               P.handCount[1] == G.handCount[1]);
    
    return 0;
}