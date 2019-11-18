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
    int minionPos;
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

        int gainCoin, discardAndRedraw;
        //Randomly generate the player's inputs for choice1 and choice2:
        gainCoin = rand() % 2;
        discardAndRedraw = rand() % 2;

        //Randomize player's hands, decks, and discard piles:
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

        //set current player:
        G.whoseTurn = currentPlayer;

        //Generate a guaranteed Minion card for the current player:
        if(G.handCount[currentPlayer] != 0) {
            minionPos = rand() % G.handCount[currentPlayer];
            G.hand[currentPlayer][minionPos] = minion;
        } else {
            minionPos = 0;
            G.handCount[currentPlayer] = 1;
            G.hand[currentPlayer][minionPos] = minion;
        }
        
        //save game state:
        P = G;
        playMinion(minionPos, currentPlayer, gainCoin, discardAndRedraw, &G);

        failed = FALSE;
        char message[256];

        //Check that single state values remain unaffected:
        if(customAssert("\tgameState.numPlayers corrupted", P.numPlayers == G.numPlayers))                                          {failed = TRUE;}
        if(customAssert("\tgameState.outpostPlayed corrupted", P.outpostPlayed == G.outpostPlayed))                                 {failed = TRUE;}
        if(customAssert("\tgameState.outpostTurn corrupted", P.outpostTurn == G.outpostTurn))                                       {failed = TRUE;}
        if(customAssert("\tgameState.whoseTurn corrupted", P.whoseTurn == G.whoseTurn))                                             {failed = TRUE;}
        if(customAssert("\tgameState.phase corrupted", P.phase == G.phase))                                                         {failed = TRUE;}
        if(customAssert("\tgameState.numBuys corrupted", P.numBuys == G.numBuys))                                                   {failed = TRUE;}
        if(customAssert("\tgameState.playedCardCount corrupted", P.playedCardCount == G.playedCardCount))                           {failed = TRUE;}
        if(customAssert("\tgameState.numActions corrupted/incremented incorrectly", (P.numActions + 1) == G.numActions))            {failed = TRUE;}

        //Cases where coin should be increased and no other changes should be made:
        if( (gainCoin == TRUE && discardAndRedraw == FALSE) || (gainCoin == TRUE && discardAndRedraw == TRUE) ) {
            if(customAssert("\tgameState.numActions corrupted/incremented incorrectly", (P.numActions + 1) == G.numActions))        {failed = TRUE;}
            if(customAssert("\tgameState.coins corrupted/incremented incorrectly", G.coins == (P.coins + 2)))                       {failed = TRUE;}
            if(customAssert("\tplayed Minion card was not removed from hand", G.hand[currentPlayer][minionPos] == minion))          {failed = TRUE;}
            if(customAssert("\tcurrent player's discardCount corrupted/not changed correctly", G.discardCount[currentPlayer] == (G.discardCount[currentPlayer] + 1))) {failed = TRUE;}
            if(customAssert("\tcurrentPlayer's top discard is not a Minion", G.discard[currentPlayer][G.discardCount[currentPlayer]]))  {failed = TRUE;}
            //Check that all player's hands/decks/discards remained static:
            for (int k = 0; k < G.numPlayers; k++) {
                if(k != currentPlayer){
                    sprintf(message, "\tPlayer %d's hand array corrupted/erroneously modified.", k);
                    if(customAssert(message, memcmp(&(G.hand[k]), &(G.hand[k]), sizeof(int)* MAX_HAND) == 0))                       {failed = TRUE;}
                    sprintf(message, "\tPlayer %d's deck array corrupted/erroneously modified.", k);
                    if(customAssert(message, memcmp(&(G.deck[k]), &(G.deck[k]), sizeof(int)* MAX_DECK) == 0))                       {failed = TRUE;}
                    sprintf(message, "\tPlayer %d's discard array corrupted/erroneously modified.", k);
                    if(customAssert(message, memcmp(&(G.discard[k]), &(G.discard[k]), sizeof(int)* MAX_DECK) == 0))                 {failed = TRUE;}
                }
            }

        }
        //Case where hands should be redrawn and no coin given:
        else if( gainCoin == FALSE && discardAndRedraw == TRUE) {
            if(customAssert("\tgameState.numActions corrupted/incremented incorrectly", (P.numActions + 1) == G.numActions))        {failed = TRUE;}
            for (int k = 0; k < G.numPlayers; k++) {
                if (k != currentPlayer) {
                    if (P.handCount[k] > 4) {
                        sprintf(message, "\tEligible player %d's hand not redrawn to 4 cards.", k);
                        if(customAssert(message, (G.handCount[k] == 4)))                                                            {failed = TRUE;}
                    }
                }
            }
            if(customAssert("\tCurrent player's hand not redrawn.", G.handCount[currentPlayer] == 4))                               {failed = TRUE;}

        }
        //Case where no valid option is given to the function. No changes should be made to the game state:
        else if ( gainCoin == FALSE && discardAndRedraw == FALSE) {
            if(customAssert("\tgameState.numActions corrupted/incremented incorrectly", P.numActions == G.numActions))              {failed = TRUE;}    //When no valid option is given *no* changes should be made
            if(customAssert("\tgameState.coins corrupted", G.coins == P.coins))                                                     {failed = TRUE;}
            //Check that all players' hands/decks/discards/remained static:
            for (int k = 0; k < G.numPlayers; k++) {
                sprintf(message, "Player %d's hand array corrupted/erroneously modified.", k);
                if(customAssert(message, memcmp(&(G.hand[k]), &(G.hand[k]), sizeof(int)* MAX_HAND) == 0))                           {failed = TRUE;}
                sprintf(message, "Player %d's deck array corrupted/erroneously modified.", k);
                if(customAssert(message, memcmp(&(G.deck[k]), &(G.deck[k]), sizeof(int)* MAX_DECK) == 0))                           {failed = TRUE;}
                sprintf(message, "Player %d's discard array corrupted/erroneously modified.", k);
                if(customAssert(message, memcmp(&(G.discard[k]), &(G.discard[k]), sizeof(int)* MAX_DECK) == 0))                     {failed = TRUE;}
            }

        }

        if (failed == TRUE) {
            totalFailedTests++;
            printf("Above failures occured on Iteration %d\nNumber of Players: %d - Current Player: %d\n", (i + 1), G.numPlayers, G.whoseTurn);
            printf("Input parameters: choice1: %d - choice2: %d\n\n", gainCoin, discardAndRedraw);
        }

    }

    printf("\n*****TOTAL RANDOM TESTS FAILED:\t %d/%d", totalFailedTests, iterations);
    printf("\n*****PERCENTAGE FAILED:\t\t %f\n", (float)totalFailedTests / (float)iterations);

    return 0;
}
