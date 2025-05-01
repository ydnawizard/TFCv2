#ifndef PLAYMENU_H
#define PLAYMENU_H

char* playOptsRaw[5]={"Deck:","Timer","Repeat:","Orientation:","PLAY"};

void assignPlayOpts(char*** playOpts)
{
	(*playOpts)=malloc(5*sizeof(char*));
	for(int i=0;i<5;i++)
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
	while(menuState>=0)
	{
		mvwprintw((*titleWin),1,1,"Game Settings:\n");
		wrefresh((*titleWin));
		wclear((*menuWin));
		for(int i=0;i<5;i++)
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
					decksMenu(&(*menuWin),&(*titleWin),&(*gameRules));
					catDeckName(&playOpts,(*gameRules),prevDeckSize);
					prevDeckSize=strlen(gameRules->DECK.NAME);
				}else if(highlight==1)
				{
					//deckBuilder();
				}else if(highlight==2)
				{
					//clientMenu();
				}else if(highlight==3)
				{
					//statsMenu();
				}else if(highlight==4)
				{
					//infoMenu();
				}else
				{
					exit(0);
				}
				break;
			case KEY_LEFT:
				menuState=-1;
			default:
				break;
		}
	}
}

#endif
