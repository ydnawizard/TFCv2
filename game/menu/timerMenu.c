//I know there are some redundancies in here but they are extremely minor
//Pls be nice I wrote this while badly withdrawing from alcahawl

//timerOptsRaw contains the base state of the the menu
//this is dumped into array (timerOpts) each time the menu is updated.
//This allows the menu to be changed without writing a massive loop where
//we add each base menu string to each field and then cat the new time value every iteration
char* timerOptsRaw[6]={" ","Seconds Per Card:"," "," ","Minutes In Game:"," "};

//Dump timerOptsRaw into timerOpts so the fields can be mutated
void assignTimerOpts(char*** timerOpts)
{
	(*timerOpts)=malloc(6*sizeof(char*));
	for(int i=0;i<6;i++)
	{
		(*timerOpts)[i]=malloc(strlen(timerOptsRaw[i])*sizeof(char));
		strcpy((*timerOpts)[i],timerOptsRaw[i]);
	}
}
	
//Concatenate the card time field to the end of the timer per card menu field
void catCardTimeFields(char*** timerOpts,struct GAMERULES gameRules)
{
	//Initialize a temp string to hold timer value
	char timer[8];
	//convert card timer int to string and dump into timer
	sprintf(timer,"%d",gameRules.CARD_TIMER);
	//realloc timerOpts to make space for concatenation
	(*timerOpts)[1]=realloc((*timerOpts)[1],strlen(timerOptsRaw[1])+strlen(timer)*sizeof(char));
	//set timerOpts[1] (timer per card:) to null terminators to get rid of previous 
	//concatenation if there was one
	memset((*timerOpts)[1],'\0',strlen((*timerOpts)[1]));
	//copy timerOptsRaw[1] into timerOpts[1]
	strcpy((*timerOpts)[1],timerOptsRaw[1]);
	//concatenate timer value
	strcat((*timerOpts)[1],timer);
}

//Concatenate the game time field to the end of the timer per game menu field
void catGameTimeFields(char*** timerOpts,struct GAMERULES gameRules)
{
	char timer[8];
	sprintf(timer,"%d",gameRules.GAME_TIMER);
	(*timerOpts)[4]=realloc((*timerOpts)[4],strlen(timerOptsRaw[4])+strlen(timer)*sizeof(char));
	memset((*timerOpts)[4],'\0',strlen((*timerOpts)[4]));
	strcpy((*timerOpts)[4],timerOptsRaw[4]);
	strcat((*timerOpts)[4],timer);
}

//Ease of use
void catTimeFields(char*** timerOpts,struct GAMERULES gameRules)
{
	catCardTimeFields(&(*timerOpts),gameRules);
	catGameTimeFields(&(*timerOpts),gameRules);
}




//Timer menu loop
void timerMenu(WINDOW** menuWin,WINDOW** titleWin,struct GAMERULES* gameRules)
{
	//clear screen
	clear();
	refresh();
	//key pressed
	int key;
	//menuState
	int menuState=0;
	int highlight=1;
	char** timerOpts;
	//Init timer opts
	assignTimerOpts(&timerOpts);
	//Cat time values
	catTimeFields(&timerOpts,(*gameRules));
	//While menuState >= 0
	while(menuState>=0)
	{
		//Print title
		mvwprintw((*titleWin),1,1,"Timer Settings: (Enter To Accept)");
		wrefresh((*titleWin));
		wclear((*menuWin));
		//Print menu and highlight relevant option
		for(int i=0;i<6;i++)
		{
			if(i==highlight)
			{
				wattron((*menuWin),A_REVERSE);
			}
			mvwprintw((*menuWin),i+1,1,timerOpts[i]);
			wattroff((*menuWin),A_REVERSE);
		}
		wrefresh((*menuWin));
		//get key pressed
		key=wgetch((*menuWin));
		//if key is:
		switch(key)
		{
			//Up arrow
			case KEY_UP:
				if(highlight==1)
				{
					break;
				}else
				{
					highlight-=3;
					break;
				}
			//Down arrow
			case KEY_DOWN:
				if(highlight==4)
				{
					break;
				}else
				{
					highlight+=3;
					break;
				}
			//Right arrow
			case KEY_RIGHT:
				//If highlight is 1 and card time is not at limit:
				if(highlight==1&&gameRules->CARD_TIMER!=10000)
				{
					//increment card timer
					gameRules->CARD_TIMER+=5;
					//concatenate new timer value with menu field
					catTimeFields(&timerOpts,(*gameRules));
				}else if(highlight==4&&gameRules->GAME_TIMER!=1000)
				{
					gameRules->GAME_TIMER+=1;
					catTimeFields(&timerOpts,(*gameRules));
				}
				break;
			case KEY_LEFT:
				if(highlight==1&&gameRules->CARD_TIMER!=0)
				{
					gameRules->CARD_TIMER-=5;
					catTimeFields(&timerOpts,(*gameRules));
				}else if(highlight==4&&gameRules->GAME_TIMER!=0)
				{
					gameRules->GAME_TIMER-=1;
					catTimeFields(&timerOpts,(*gameRules));
				}
				break;
			case '\n':
				menuState-=1;
		}
	}
}

