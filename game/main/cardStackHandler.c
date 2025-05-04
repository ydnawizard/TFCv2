
//Return true if card id is in the drawn card array. Drawn card array is DRAWN in GAMESTATE
bool checkIfDrawn(struct GAMESTATE gameState,struct GAMERULES gameRules,int randInt)
{
	for(int i=0;i<gameState.DRAWN_COUNT;i++)
	{
		if(gameState.DRAWN[i]==randInt)
		{
			return true;
		}
	}
	return false;
}

//Handles each combination of shuffle and repeat
void cardStackHandler(struct GAMESTATE* gameState,struct GAMERULES gameRules)
{
	if(((*gameState).CARD.ID==gameRules.DECK.CARD_COUNT)&&gameRules.REPEAT==false)
	{
		exit(0);
	}
	//Roll random int between 0 and DECK CARD_COUNT
	//If check drawn on rand int returns true, roll again and increment i
	//If i == DECK CARD_COUNT, end game.
	else if(gameRules.SHUFFLE==true&&gameRules.REPEAT==FALSE)
	{
		int randInt=rand()%gameRules.DECK.CARD_COUNT;
		int i=0;
		while(checkIfDrawn((*gameState),gameRules,randInt)==true)
		{
			if(i==gameRules.DECK.CARD_COUNT)
			{
				(*gameState).STATE-=1;
			}
			randInt=rand()%gameRules.DECK.CARD_COUNT;
			i+=1;
		}
		//Increment drawn card count
		(*gameState).DRAWN_COUNT+=1;
		//make space for drawn card
		(*gameState).DRAWN=realloc((*gameState).DRAWN,(*gameState).DRAWN_COUNT*sizeof(int));
		//add drawn card to drawn
		(*gameState).DRAWN[(*gameState).DRAWN_COUNT-1]=randInt;
		//change gamestate card to Cards[randint]
		(*gameState).CARD=gameRules.DECK.CARDS[randInt];
	}
	else if(gameRules.SHUFFLE==true&&gameRules.REPEAT==TRUE)
	{
		int randInt=rand()%gameRules.DECK.CARD_COUNT;
		(*gameState).CARD=gameRules.DECK.CARDS[randInt];
	}
	else
	{

		(*gameState).CARD=gameRules.DECK.CARDS[(*gameState).CARD.ID+=1];
	}
}
