
void initGameState(struct GAMESTATE* gameState,struct GAMERULES gameRules)
{
	(*gameState).STATE=1;
	(*gameState).CARD_CLOCK=gameRules.CARD_TIMER;
	(*gameState).GAME_CLOCK=gameRules.GAME_TIMER;
	if(gameRules.SHUFFLE==true)
	{
		int randInt=rand()%gameRules.DECK.CARD_COUNT;
		(*gameState).CARD=gameRules.DECK.CARDS[randInt];
		(*gameState).DRAWN=malloc(sizeof(int));
		(*gameState).DRAWN[0]=(*gameState).CARD.ID;
		(*gameState).DRAWN_COUNT=1;
	}else
	{
		(*gameState).CARD=gameRules.DECK.CARDS[0];
		(*gameState).DRAWN=malloc(sizeof(int));
		(*gameState).DRAWN[0]=(*gameState).CARD.ID;
		(*gameState).DRAWN_COUNT=1;
	}
}

void printQuery(WINDOW** questionWin,struct GAMESTATE gameState,struct GAMERULES gameRules)
{
	if(gameRules.ORIENTATION==1)
	{
		mvwprintw((*questionWin),1,1,"%s\n",gameState.CARD.FRONT);
		wborder((*questionWin),ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
		wrefresh((*questionWin));
	}else
	{

		mvwprintw((*questionWin),1,1,"%s\n",gameState.CARD.BACK);
		wrefresh((*questionWin));
	}
}

void answerHandler(WINDOW** answerWin,struct GAMESTATE gameState,struct GAMERULES gameRules,char inputChar,char** inputStr,int* strLen)
{
	if(inputChar=='\n')
	{
		if(strcmp(gameState.CARD.BACK,(*inputStr))==0&&gameRules.ORIENTATION==1)
		{
			exit(0);
		}
		else if(strcmp(gameState.CARD.FRONT,(*inputStr))==0&&gameRules.ORIENTATION==0)
		{
			exit(0);
		}
	}else
	{
		(*inputStr)=realloc((*inputStr),(*strLen)+1*sizeof(char));
		(*inputStr)[(*strLen)-1]=inputChar;
		(*inputStr)[(*strLen)]='\0';
		(*strLen)+=1;
		mvwprintw((*answerWin),1,1,"%s",(*inputStr));
	}
}
		

void playGame(WINDOW* menuWin,WINDOW* titleWin,struct GAMERULES gameRules,char** playOpts)
{
	clear();
	refresh();
	srand(time(NULL));
	int key;
	WINDOW* questionWin=newwin(10,45,15,25);
	WINDOW* answerWin=newwin(3,67,25,25);
	WINDOW* rulesWin=newwin(10,22,15,70);
	wborder(questionWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(answerWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(rulesWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	struct GAMESTATE gameState;
	initGameState(&gameState,gameRules);
	mvwprintw(rulesWin,1,1,playOpts[0]);
	mvwprintw(rulesWin,2,1,playOpts[2]);
	mvwprintw(rulesWin,3,1,playOpts[3]);
	mvwprintw(rulesWin,4,1,playOpts[4]);
	mvwprintw(rulesWin,5,1,"Card #:%d",gameState.CARD.ID);
	char inputChar;
	char* inputStr=malloc(2*sizeof(char));
	inputStr[0]='a';
	inputStr[1]='\0';
	int strLen=1;
	int ticker=0;
	time_t initialTime=time(0),initialGameTime=initialTime;
	while(gameState.STATE>0)
	{
		time_t currentTime=time(0);
		clockHandler(&rulesWin,&gameState,gameRules,&initialGameTime,&initialTime,currentTime);
		printQuery(&questionWin,gameState,gameRules);
		mvwprintw(rulesWin,5,1,"Card #:%d",gameState.CARD.ID);
		if(kbhit())
		{
			inputChar = wgetch(answerWin);
			answerHandler(&answerWin,gameState,gameRules,inputChar,&inputStr,&strLen);
		}
		ticker+=1;
		wrefresh(answerWin);
	}
	clear();
	refresh();
	wrefresh(menuWin);
	wrefresh(titleWin);
}

