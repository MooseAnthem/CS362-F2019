#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"

int playBaron(struct gameState* state, int choice, int currentPlayer)
{
	state->numBuys++; //increase the number of buys for the current player
	if ( choice == TRUE ){
		int p = 0;
			//Search player's hand for an estate. If one is found, position is returned.
			//`-1` indicates no estate was found.
			if ( (p = cardInHand(estate, state, currentPlayer)) != -1 ) {
				state->coins += 4;
				state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
				state->discardCount[currentPlayer]++;
				//Remove the estate card from the player's hand
				for (; p < state->handCount[currentPlayer]; p++) {
					state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
					
				}
				state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
				state->handCount[currentPlayer]--;
			}
			else {
				if (DEBUG) {
					printf("No estate cards exist in your hand. Invalid choice.\n");
					printf("Must gain an estate if any exist in supply.\n");
				}
				if (supplyCount(estate, state) > 0) {
					gainCard(estate, state, 0, currentPlayer);
					
					state->supplyCount[estate]--;
					if (supplyCount(estate, state) == 0) {
						isGameOver(state);
					}
				}
			}
	}
	//If player chose to gain an estate by providing `choice = 0`
	else {
		if (supplyCount(estate, state) > 0) {
			gainCard(estate, state, 0, currentPlayer);
			
			state->supplyCount[estate]--;
			if(supplyCount(estate, state) == 0) {
				isGameOver(state);
			}
		}

	}

	return 0;
}
 
					
int cardInHand(enum CARD targetCard, struct gameState *state, int currentPlayer) {
	for(int pos = 0; pos < state->handCount[currentPlayer]; pos++) {
		if ( state->hand[currentPlayer][pos] == targetCard ) {
			return pos;
		}
	} 
	
	return -1;
}

int playTribute(int currentPlayer, int nextPlayer, struct gameState *state) {
	//Create array to store the cards revealed by the next player:
	int tributeRevealedCards[2] = {-1, -1};
	
	//Determine whether the next player only has at least 2 cards in their combined hand & deck.
	//If not, the next player either reveals their single card or doesn't reveal anything:  
	if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
        if (state->deckCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
            state->deckCount[nextPlayer]--;
        }
        else if (state->discardCount[nextPlayer] > 0) {
            tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
            state->discardCount[nextPlayer]--;
        }
        else {
            //No Card to Reveal
            if (DEBUG) {
                printf("No cards to reveal\n");
            }
        }
	}

	//If the next player does have at least 2 cards:
	else {
		//Check if deck is empty and if so, add 
        if (state->deckCount[nextPlayer] == 0) {
            for (int i = 0; i < state->discardCount[nextPlayer]; i++) {
                state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
                state->deckCount[nextPlayer]++;
                state->discard[nextPlayer][i] = -1;
                state->discardCount[nextPlayer]--;
            }

            shuffle(nextPlayer,state);//Shuffle the deck
        }
        tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
        state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
        state->deckCount[nextPlayer]--;
        tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
        state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
        state->deckCount[nextPlayer]--;
    }

	//Check if the two cards revealed are duplicates:
	if (tributeRevealedCards[0] == tributeRevealedCards[1]) { //If we have a duplicate card, just drop one
            state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
            state->playedCardCount++;
            tributeRevealedCards[1] = -1;
        }

	//Check the cards in the tribute card array and give appropiate bonuses for each:
	for (int i = 0; i <= 2; i ++) {
			//This series of if statements ensures that a duplicate card changed to `-1` does not give any bonuses:
            if (tributeRevealedCards[i] >= copper && tributeRevealedCards[i] <= gold) { //Treasure cards
                state->coins += 2;
            }

            if ((tributeRevealedCards[i] >= estate && tributeRevealedCards[i] <= province) || tributeRevealedCards[i] == gardens) { //Victory Card Found
                drawCard(currentPlayer, state);
                drawCard(currentPlayer, state);
            }
            if ((tributeRevealedCards[i] >= adventurer && tributeRevealedCards[i] <= treasure_map) && tributeRevealedCards[i] != gardens) { //Action Card Found
                state->numActions = state->numActions + 2;
			}
        }

    return 0;

}