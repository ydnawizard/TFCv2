
//Ticks the card clock down in gamestate. If clock is zero, reset.
void tickCardClock(struct GAMERULES gameRules,struct GAMESTATE* gameState,time_t* initialTime,time_t currentTime)
{
	int ticker=getTimeDiffSeconds(currentTime,(*initialTime));
	if(ticker==gameRules.CARD_TIMER)
	{
		gameState->CARD_CLOCK=gameRules.CARD_TIMER;
		(*initialTime)=time(0);
		cardStackHandler(&(*gameState),gameRules);
	}else
	{
		gameState->CARD_CLOCK=gameRules.CARD_TIMER-ticker;
	}
}

//Ticks the game clock down in gamestate
void tickGameClock(struct GAMERULES gameRules,struct GAMESTATE* gameState,time_t* initialGameTime,time_t currentTime)
{
	//get time difference
	int ticker=getTimeDiffMinutes(currentTime,(*initialGameTime));
	//If one minute has passed:
	if(ticker>=1)
	{
		//Tick gamestate clock down 1 minute
		gameState->GAME_CLOCK-=1;
		//Reset reference game time
		(*initialGameTime)=time(0);
	}
}

//Handles printing the clock to the window. This is necessary because without the space before
//a single digit, a residual digit will be left from previous print statements
void printCardClock(WINDOW** rulesWin,struct GAMESTATE gameState)
{
	if(gameState.CARD_CLOCK<10)
	{
		mvwprintw((*rulesWin),6,1,"Card Timer: %d",gameState.CARD_CLOCK);
		wrefresh((*rulesWin));
	}else
	{
		mvwprintw((*rulesWin),6,1,"Card Timer:%d",gameState.CARD_CLOCK);
		wrefresh((*rulesWin));
	}
}

//Same as printCardClock
void printGameClock(WINDOW** rulesWin,struct GAMESTATE gameState)
{
	if(gameState.GAME_CLOCK<10)
	{
		mvwprintw((*rulesWin),7,1,"Game Timer: %d",gameState.GAME_CLOCK);
		wrefresh((*rulesWin));
	}else
	{
		mvwprintw((*rulesWin),7,1,"Game Timer:%d",gameState.GAME_CLOCK);
		wrefresh((*rulesWin));
	}
}

//Tie it all together
void clockHandler(WINDOW** rulesWin,struct GAMESTATE* gameState,struct GAMERULES gameRules,time_t* initialGameTime,time_t* initialTime,time_t currentTime)
{
	if(gameRules.CARD_TIMER>0&&gameRules.GAME_TIMER>0)
	{
		tickCardClock(gameRules,&(*gameState),&(*initialGameTime),currentTime);
		tickGameClock(gameRules,&(*gameState),&(*initialTime),currentTime);
		printCardClock(&(*rulesWin),(*gameState));
		printGameClock(&(*rulesWin),(*gameState));
	}else if(gameRules.CARD_TIMER>0&&gameRules.GAME_TIMER==0)
	{
		tickCardClock(gameRules,&(*gameState),&(*initialGameTime),currentTime);
		printCardClock(&(*rulesWin),(*gameState));
		printGameClock(&(*rulesWin),(*gameState));
	}else if(gameRules.CARD_TIMER==0&&gameRules.GAME_TIMER>0)
	{
		tickGameClock(gameRules,&(*gameState),&(*initialTime),currentTime);
		printCardClock(&(*rulesWin),(*gameState));
		printGameClock(&(*rulesWin),(*gameState));
	}else
	{
		printCardClock(&(*rulesWin),(*gameState));
		printGameClock(&(*rulesWin),(*gameState));
	}
}

