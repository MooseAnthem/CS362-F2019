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
				state->discardcount[currentPlayer]++;
				//Remove the estate card from the player's hand
				for (; p < state->handCount[currentPlayer]; p++) {
					state->hand[currentPLayer][p] = state->hand[currentPlayer][p+1];
					
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
 
					
int cardInHand(CARD targetCard, struct gameState *state, int currentPlayer) {
	for(int pos = 0; pos < state->handCount[currentPlayer]; pos++) {
		if ( state->hand[currentPlayer][pos] == targetCard ) {
			return pos;
		}
	} 
	
	return -1;
}
