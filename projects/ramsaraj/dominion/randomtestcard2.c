#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#include "customAssert.h"
#include "interface.h"

#define FALSE 0
#define TRUE 1

int main(int argc, char* argv[]) {

    srand(time(0));

    int iterations = atoi(argv[1]);
    int numPlayers;
    int currentPlayer;
    struct gameState G, P;
    int failed;
    int totalFailedTests = 0;
    

    int kingdomCards[10] = {adventurer, tribute, ambassador, baron, minion, sea_hag, mine, cutpurse, council_room, salvager};  //Kingdom cards to use for the test.
    int validCards[16] = {adventurer, tribute, ambassador, baron, minion, sea_hag, mine, cutpurse, council_room, salvager, estate, duchy, province, copper, silver, gold}; //Used to randomly distribute cards to players

    for (int i = 0; i < iterations; i++) {
        memset(&G, 0, sizeof(struct gameState));    //clear game state
        numPlayers = (rand() % 3) + 2;
        currentPlayer = (rand() % numPlayers);
        initializeGame(numPlayers, kingdomCards, ((rand() % 1000) + 1), &G);

        //Generate the input domain. Each will either be TRUE or FALSE
        int WANTS_GOLD = rand() % 2;
        int HAS_ESTATE = rand() % 2;
        int ESTATE_IN_SUPPLY= rand() % 2;

        //If WANTS_GOLD is TRUE, make the input given to the function either positive
        //  or negative (TO BE ADDED):

        for (int player = 0; player < numPlayers; player++) {
            G.handCount[player] = (rand() % 20);
            for (int card = 0; card < G.handCount[player]; card++) {
                G.hand[player][card] = validCards[(rand() % 16)];
            }
            G.deckCount[player] = (rand() % 20);
            for (int card = 0; card < G.deckCount[player]; card++) {
                G.deck[player][card] = validCards[(rand() % 16)];
            }
            G.discardCount[player] = (rand() % 20);
            for (int card = 0; card < G.discardCount[player]; card++) {
                G.discard[player][card] = validCards[(rand() % 16)];
            }
        }

        //randomize supply counts:
        for (int card = adventurer; card <= treasure_map; card++)   //loop all cards
        {
            for (int j = 0; j < 10; j++)           		//loop chosen cards
            {
                if (kingdomCards[j] == card)
                {
                    G.supplyCount[card] = (rand() % 11);
                    break;
                }
            }
        }
        //randomize victory card supply counts:
        if(numPlayers == 2) {
            G.supplyCount[estate] = rand() % 8 + 1;
            G.supplyCount[duchy] = rand() % 9;
            G.supplyCount[province] = rand() % 9;
        } else {
            G.supplyCount[estate] = rand() % 12 + 1;
            G.supplyCount[duchy] = rand() % 13;
            G.supplyCount[province] = rand() % 13;
        }

        //randomize current player:
        G.whoseTurn = currentPlayer;
        int nextPlayer = G.whoseTurn + 1;
        if (nextPlayer > (G.numPlayers - 1)) {
            nextPlayer = 0;
        }

        //If HAS_ESTATE is false, remove all estates from the player's hand:
        if (HAS_ESTATE == FALSE) {
            for (int k = 0; k < G.handCount[G.whoseTurn]; k++) {
                do{
                    if(G.hand[G.whoseTurn][k] == estate){
                        G.hand[G.whoseTurn][k] = validCards[rand() % 16];
                    }
                } while(G.hand[G.whoseTurn][k] == estate);
            }
        } else {
            //ENSURE the player will have at least 1 estate in their hand:
            if(G.handCount[currentPlayer] > 0) {    //Need to ensure that the player doesn't have 0 cards - this will cause a floating point exception from the modulus.
                G.hand[currentPlayer][rand() % G.handCount[currentPlayer]] = estate;
            }
        }

        //If ESTATE_IN_SUPPLY is FALSE, make the supply count of Estate 0:
        if(ESTATE_IN_SUPPLY == FALSE) {
            G.supplyCount[estate] = 0;
        }

        //randomize starting coins:
        int startingCoin = G.coins = rand() % 101;

        P = G;  //save game state
        failed = FALSE;

        
        char wantsBool[256];
        if(WANTS_GOLD == TRUE){
            sprintf(wantsBool, "TRUE");
        }else{
            sprintf(wantsBool, "FALSE");
        }
        char hasBool[256];
        if(HAS_ESTATE == TRUE){
            sprintf(hasBool, "TRUE");
        }else{
            sprintf(hasBool, "FALSE");
        }
        char estateBool[256];
        if(ESTATE_IN_SUPPLY == TRUE){
            sprintf(estateBool, "TRUE");
        }else{
            sprintf(estateBool, "FALSE");
        }
       
        playBaron(WANTS_GOLD, currentPlayer, &G);
        
        //Output where player should recieve +4 gold and discard an Estate:
        if(WANTS_GOLD == TRUE && HAS_ESTATE == TRUE){
            //printf("---Current player should discard Estate, coins should increase by 4 ---\n");
            if(customAssert("\tGold not increased by 4.", G.coins == (P.coins + 4))) {failed = TRUE;}
            if(customAssert("\tG.discardCount[currentPlayer] incorrectly updated.", G.discardCount[G.whoseTurn] == P.discardCount[G.whoseTurn])) {failed = TRUE;}
            if(customAssert("\tTop of current player's discard array not an Estate after discarding Estate.", G.discard[G.whoseTurn][P.discardCount[G.whoseTurn]] == estate)) {failed = TRUE;}
            if(customAssert("\tG.supplyCount[] array incorrectly modified.", memcmp(&(G.supplyCount), &(P.supplyCount), sizeof(int) * (treasure_map + 1)))) {failed = TRUE;}
        }
        //Output where nothing should be happening:
        if((WANTS_GOLD == FALSE && ESTATE_IN_SUPPLY == FALSE) || (WANTS_GOLD == TRUE && HAS_ESTATE == FALSE && ESTATE_IN_SUPPLY == FALSE)) {
            //printf("---No changes should be applied to coins, or current player's discard & hand arrays/counts---");
            if(customAssert("\tCoins incorrectly modified.", G.coins == P.coins)) {failed = TRUE;}
            if(customAssert("\tCurrent player's discard count incorrectly modified.", G.discardCount[currentPlayer] == P.discardCount[currentPlayer])) {failed = TRUE;}
            if(customAssert("\tCurrent player's discard array incorrectly modified.", memcmp(&(G.discard[currentPlayer]), &(P.discard[currentPlayer]), sizeof(int) * MAX_DECK) == 0)) {failed = TRUE;}
            if(customAssert("\tCurrent player's hand array incorrectly modified.", memcmp(&(G.hand[currentPlayer]), &(P.hand[currentPlayer]), sizeof(int) * MAX_HAND) == 0)) {failed = TRUE;}
            if(customAssert("\tG.supplyCount[] array incorrectly modified.", memcmp(&(G.supplyCount), &(P.supplyCount), sizeof(int) * (treasure_map + 1)) == 0)) {failed = TRUE;}
        }
        //Output where player should recieve an estate from the supply:
        if((WANTS_GOLD == TRUE && HAS_ESTATE == FALSE && ESTATE_IN_SUPPLY == TRUE) || (WANTS_GOLD == FALSE && ESTATE_IN_SUPPLY == TRUE)) {
            //printf("---Current player should recieve Estate, Estate should be on top of current player's discard, coins remain static---");
            if(customAssert("\tEstate Supply incorrectly modified.",G.supplyCount[estate] == (P.supplyCount[estate] - 1) )) {failed = TRUE;}
            if(customAssert("\tTop of current player's discard is not Estate.", G.discard[currentPlayer][P.discardCount[currentPlayer]] == estate)) {failed = TRUE;}
            if(customAssert("\tG.discardCount[currentPlayer] incorrectly updated.", G.discardCount[currentPlayer] == (P.discardCount[currentPlayer] + 1) )) {failed = TRUE;}
            if(customAssert("\tG.coins incorrectly modified.", G.coins == P.coins) == FALSE) {failed = TRUE;}
        }

        //Ensure that game state has not been corrupted:
        if(customAssert("\tgameState.numPlayers corrupted", P.numPlayers == G.numPlayers))                      {failed = TRUE;}
        if(customAssert("\tgameState.outpostPlayed corrupted", P.outpostPlayed == G.outpostPlayed))             {failed = TRUE;}
        if(customAssert("\tgameState.outpostTurn corrupted", P.outpostTurn == G.outpostTurn))                   {failed = TRUE;}
        if(customAssert("\tgameState.whoseTurn corrupted", P.whoseTurn == G.whoseTurn))                         {failed = TRUE;}
        if(customAssert("\tgameState.phase corrupted", P.phase == G.phase))                                     {failed = TRUE;}
        if(customAssert("\tgameState.numBuys corrupted", (P.numBuys + 1) == G.numBuys))                         {failed = TRUE;}
        if(customAssert("\tgameState.playedCardCount corrupted", P.playedCardCount == G.playedCardCount))       {failed = TRUE;}

        //Check whether uninvolved player's hand arrays have been corrupted:
        for (int k = 0; k < G.numPlayers; k++) {
            if (k != currentPlayer) {
                char message[256];
                sprintf(message, "\tPlayer %d's hand array corrupted (G.hand[%d][MAX_HAND])", k, k);
                if(customAssert(message, memcmp(&(G.hand[k]), &(P.hand[k]), sizeof(int) * MAX_HAND) == 0)) {failed = TRUE;};
                sprintf(message, "\tPlayer %d's handCount corrupted (G.handCount[%d])", k, k);
                if(customAssert(message, P.handCount[k] == G.handCount[k])) {failed = TRUE;};
            }
        }
        //Check whether uninvolved player's decks have been corrupted:
        for (int k = 0; k < G.numPlayers; k++) {
            if (k != currentPlayer) {
                char message[256];
                sprintf(message, "\tPlayer %d's deck array corrupted (G.deck[%d][MAX_HAND])", k, k);
                if(customAssert(message, memcmp(&(G.deck[k]), &(P.deck[k]), sizeof(int) * MAX_HAND) == 0)) {failed = TRUE;};
                sprintf(message, "\tPlayer %d's deckCount corrupted (G.deckCount[%d])", k, k);
                if(customAssert(message, P.deckCount[k] == G.deckCount[k])) {failed = TRUE;};
            }
        }
        //Check whether uninvolved player's discards have been corrupted:
        for (int k = 0; k < G.numPlayers; k++) {
            if (k != currentPlayer) {
                char message[256];
                sprintf(message, "\tPlayer %d's discard array corrupted (G.discard[%d][MAX_HAND])", k, k);
                if(customAssert(message, memcmp(&(G.discard[k]), &(P.discard[k]), sizeof(int) * MAX_HAND) == 0)) {failed = TRUE;};
                sprintf(message, "\tPlayer %d's discardCount corrupted (G.discardCount[%d])", k, k);
                if(customAssert(message, P.discardCount[k] == G.discardCount[k])) {failed = TRUE;};
            }
        }

        if (failed == TRUE) {
            totalFailedTests++;
            printf("Above failures occured on Iteration %d\nNumber of Players: %d - Current Player: %d - Starting Coin: %d - Current Coin: %d\n", (i + 1), G.numPlayers, G.whoseTurn, startingCoin, G.coins);
            printf("WANTS_GOLD == %s\tHAS_ESTATE == %s\tESTATE_IN_SUPPLY == %s\n\n", wantsBool, hasBool, estateBool);   //Prints the values of the input parameters for failure dump purposes
        }

    }

    printf("\n*****TOTAL RANDOM TESTS FAILED:\t %d/%d", totalFailedTests, iterations);
    printf("\n*****PERCENTAGE FAILED:\t\t %f\n", (float)totalFailedTests / (float)iterations);

    return 0;

}