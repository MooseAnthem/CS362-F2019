#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"

/* ---------------------------------------------------------------------
 * Plays the Baron card. Accepts arguments for whether the player
 * chooses 1) to discard an estate for bonus coin or 2) to gain an
 * estate, who the current player is, and a pointer to the gameState.
 * Updates the game state according to card rules and returns 0 upon
 * success.
 * ---------------------------------------------------------------------
 */
int playBaron(int choice, int currentPlayer, struct gameState* state) {
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

/* ---------------------------------------------------------------------
 * Checks if a given card exists in a target player's hand. If a card
 * is found, the array position of the card is returned. If no such
 * card is found, `-1` is returned to indicate failure.
 * ---------------------------------------------------------------------
 */
int cardInHand(enum CARD targetCard, struct gameState *state, int currentPlayer) {
	for(int pos = 0; pos < state->handCount[currentPlayer]; pos++) {
		if ( state->hand[currentPlayer][pos] == targetCard ) {
			return pos;
		}
	} 
	
	return -1;
}

/* ---------------------------------------------------------------------
 * Plays the Tribute card and updates the game state appropiately.
 * Accepts arguments for the current player, the next player, and a
 * pointer to the game state. Returns 0 on success.
 * 
 * NOTE: nextPlayer must be safely calculated beforehand. Simply passing
 * `currentPlayer + 1` may cause the array to go out of bounds.
 * ---------------------------------------------------------------------
 */
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

/* ---------------------------------------------------------------------
 * Plays the Ambassador card and updates the game state appropiately.
 * Takes arguments for the hand  position of the played Ambassador card,
 * the current player, what type of card the player wants to discard,
 * the quantity of copies the player wants to discard, and pointer to
 * the game state. Returns 0 on success.
 * ---------------------------------------------------------------------
 */
int playAmbassador(int handPos, int currentPlayer, int cardToDiscard, int quantityToDiscard, struct gameState* state) {
        int copies = 0;		//used to check if player has enough cards to discard

        if ( quantityToDiscard > 2 || quantityToDiscard < 0 || cardToDiscard == handPos) 
        {
            return -1;
        }

        for (int i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (i != handPos && i == state->hand[currentPlayer][cardToDiscard] && i != cardToDiscard)
            {
                copies++;
            }
        }
        if (copies < quantityToDiscard)
        {
            return -1;
        }

        if (DEBUG)
            printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][cardToDiscard]);


        //each other player gains a copy of revealed card
        for (int i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                gainCard(state->hand[currentPlayer][cardToDiscard], state, 0, i);
            }
        }

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);
		

        //trash copies of cards returned to supply
        for (int j = 0; j < quantityToDiscard; j++)
        {
            for (int i = 0; i < state->handCount[currentPlayer]; i++)
            {
                if (state->hand[currentPlayer][i] == state->hand[currentPlayer][cardToDiscard])
                {
                    discardCard(i, currentPlayer, state, 1);
                    break;
                }
            }
        }

		//increase supply count for chosen card by amount being discarded
        state->supplyCount[state->hand[currentPlayer][cardToDiscard]] += quantityToDiscard;

        return 0;

}

int playMinion(int handPos, int currentPlayer, int gainGoldOption, int discardOption, struct gameState *state) {
    
    //+1 action
    state->numActions++;

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    
    if (gainGoldOption)
    {
        state->coins = state->coins + 2;
    }
    else if (discardOption)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
    {

        //discard current player's hand and the hand of any player with 5 or more cards:
        for (int i = 0; i < state->numPlayers; i++)
        {
                //when the current player is reached, short-circuit
			    //evaluation automatically discards their hand now:
                if ( i == currentPlayer || state->handCount[i] > 4 )
                {
                    //discard hand
                    while( state->handCount[i] > 0 )
                    {
                        discardCard(handPos, i, state, 0);
                    }

                    //draw 4
                    for (int j = 0; j < 4; j++)
                    {
                        drawCard(i, state);
                    }
                }
        }

    }

    return 0;
}

int playMine(int currentPlayer, int handPos, int treasureCard /*was choice1*/, int desiredCard /*was choice2*/, struct gameState *state) {
    
    int cardToTrash = state->hand[currentPlayer][treasureCard];  //store card we will trash

    if (state->hand[currentPlayer][treasureCard] < copper || state->hand[currentPlayer][treasureCard] > gold)
    {
        return -1;
    }

    if (desiredCard > treasure_map || desiredCard < curse)
    {
        return -1;
    }

    if ( (getCost(state->hand[currentPlayer][treasureCard]) + 3) > getCost(desiredCard) )
    {
        return -1;
    }

    gainCard(desiredCard, state, 2, currentPlayer);

    //discard Mine from hand
    discardCard(handPos, currentPlayer, state, 0);

    /* 
    ---Old method for discarding the chosen treasure card, replaced below. Keeping for debugging purposes.---
    for (int i = 0; i < state->handCount[currentPlayer]; i++)
    {
        if (state->hand[currentPlayer][i] == cardToTrash) {
                discardCard(i, currentPlayer, state, 0);
                break;
        }
    }
    */

    discardCard(cardInHand(cardToTrash, state, currentPlayer), currentPlayer, state, 0);

    return 0;

}