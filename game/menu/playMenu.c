char* playOptsRaw[6]={"Deck:","Timer:","Shuffle:","Repeat:","Orientation:","PLAY"};

void assignPlayOpts(char*** playOpts)
{
	(*playOpts)=malloc(6*sizeof(char*));
	for(int i=0;i<6;i++)
	{
		(*playOpts)[i]=malloc(strlen(playOptsRaw[i])*sizeof(char));
		strcpy((*playOpts)[i],playOptsRaw[i]);
	}
}

void catDeckName(char*** playOpts,struct GAMERULES gameRules,int prevDeckSize)
{
	if(strlen(gameRules.DECK.NAME)>0)
	{
		(*playOpts)[0]=realloc((*playOpts)[0],strlen(playOptsRaw[0])+strlen(gameRules.DECK.NAME)*sizeof(char));
		memset((*playOpts)[0],'\0',strlen((*playOpts)[0]));
		strcpy((*playOpts)[0],playOptsRaw[0]);
		strcat((*playOpts)[0],gameRules.DECK.NAME);
	}
}

void catTimerOpts(char*** playOpts,struct GAMERULES gameRules)
{       
	char timer[8];
	char cardTimer[8];
	char gameTimer[8];
	sprintf(cardTimer,"%d",gameRules.CARD_TIMER);
	strcpy(timer,cardTimer);
	strcat(timer,"/");
	sprintf(gameTimer,"%d",gameRules.GAME_TIMER);
	strcat(timer,gameTimer);
	(*playOpts)[1]=realloc((*playOpts)[1],strlen(playOptsRaw[1])+strlen(timer)*sizeof(char));
	memset((*playOpts)[1],'\0',strlen((*playOpts)[1]));
	strcpy((*playOpts)[1],playOptsRaw[1]);
	strcat((*playOpts)[1],timer);
}

void catShuffleState(char*** playOpts,struct GAMERULES gameRules)
{
	if(gameRules.SHUFFLE==true)
	{
		(*playOpts)[2]=realloc((*playOpts)[2],strlen(playOptsRaw[2])+4*sizeof(char));
		memset((*playOpts)[2],'\0',strlen((*playOpts)[2]));
		strcpy((*playOpts)[2],playOptsRaw[2]);
		strcat((*playOpts)[2],"true");
	}else
	{
		(*playOpts)[2]=realloc((*playOpts)[2],strlen(playOptsRaw[2])+5*sizeof(char));
		memset((*playOpts)[2],'\0',strlen((*playOpts)[2]));
		strcpy((*playOpts)[2],playOptsRaw[2]);
		strcat((*playOpts)[2],"false");
	}
}

void catRepeatState(char*** playOpts,struct GAMERULES gameRules)
{
	if(gameRules.REPEAT==true)
	{
		(*playOpts)[3]=realloc((*playOpts)[3],strlen(playOptsRaw[3])+4*sizeof(char));
		memset((*playOpts)[3],'\0',strlen((*playOpts)[3]));
		strcpy((*playOpts)[3],playOptsRaw[3]);
		strcat((*playOpts)[3],"true");
	}else
	{
		(*playOpts)[3]=realloc((*playOpts)[3],strlen(playOptsRaw[3])+5*sizeof(char));
		memset((*playOpts)[3],'\0',strlen((*playOpts)[3]));
		strcpy((*playOpts)[3],playOptsRaw[3]);
		strcat((*playOpts)[3],"false");
	}
}


void catOrientation(char*** playOpts,struct GAMERULES gameRules)
{
	if(gameRules.ORIENTATION==1)
	{
		(*playOpts)[4]=realloc((*playOpts)[4],strlen(playOptsRaw[4])+5*sizeof(char));
		memset((*playOpts)[4],'\0',strlen((*playOpts)[4]));
		strcpy((*playOpts)[4],playOptsRaw[4]);
		strcat((*playOpts)[4],"front");
	}else
	{
		(*playOpts)[4]=realloc((*playOpts)[4],strlen(playOptsRaw[4])+4*sizeof(char));
		memset((*playOpts)[4],'\0',strlen((*playOpts)[4]));
		strcpy((*playOpts)[4],playOptsRaw[4]);
		strcat((*playOpts)[4],"back");
	}
}


void playMenu(WINDOW** menuWin,WINDOW** titleWin,struct GAMERULES* gameRules)
{
	clear();
	refresh();
	int key;
	int menuState=0;
	int highlight=0;
	int pathCount=0;
	int currentMenu[2]={0,0};
	char** playOpts;
	assignPlayOpts(&playOpts);
	int prevDeckSize=0;
	catDeckName(&playOpts,(*gameRules),prevDeckSize);
	catTimerOpts(&playOpts,(*gameRules));
	catShuffleState(&playOpts,(*gameRules));
	catRepeatState(&playOpts,(*gameRules));
	catOrientation(&playOpts,(*gameRules));
	while((*gameRules).PLAY==1)
	{
		wclear((*titleWin));                              
		mvwprintw((*titleWin),1,1,"Game Settings:\n");
		wrefresh((*titleWin));
		wclear((*menuWin));
		for(int i=0;i<6;i++)
		{
			if(i==highlight)
			{
				wattron((*menuWin),A_REVERSE);
			}
			mvwprintw((*menuWin),i+1,1,playOpts[i]);
			wattroff((*menuWin),A_REVERSE);
		}
		wrefresh((*menuWin));
		key=wgetch((*menuWin));
		switch(key)
		{
			case KEY_UP:
				if(highlight==0)
				{
					break;
				}else
				{
					highlight--;
					break;
				}
			case KEY_DOWN:
				if(highlight==5)
				{
					break;
				}else
				{
					highlight++;
					break;
				}
			case KEY_RIGHT:
				if(highlight==0)
				{
					(*gameRules).PLAY=2;
					decksMenu(&(*menuWin),&(*titleWin),&(*gameRules));
					catDeckName(&playOpts,(*gameRules),prevDeckSize);
					prevDeckSize=strlen(gameRules->DECK.NAME);
				}else if(highlight==1)
				{
					(*gameRules).PLAY=3;
					timerMenu(&(*menuWin),&(*titleWin),&(*gameRules));
					catTimerOpts(&playOpts,(*gameRules));
				}else if(highlight==2)
				{
					gameRules->SHUFFLE=boolFlip(gameRules->SHUFFLE);
					catShuffleState(&playOpts,(*gameRules));
				}else if(highlight==3)
				{
					gameRules->REPEAT=boolFlip(gameRules->REPEAT);
					catRepeatState(&playOpts,(*gameRules));
				}else if(highlight==4)
				{
					gameRules->ORIENTATION=bitFlip(gameRules->ORIENTATION);
					catOrientation(&playOpts,(*gameRules));
				}else if(highlight==5)
				{
					(*gameRules).PLAY=0;
					playGame((*menuWin),(*titleWin),(*gameRules),playOpts);
				}
				break;
			case KEY_LEFT:
				(*gameRules).PLAY=-1;
			default:
				break;
		}
	}
}

