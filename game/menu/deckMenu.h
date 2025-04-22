#ifndef DECKMENU_H
#define DECKMENU_H


void decksMenu(WINDOW** menuWin,WINDOW** titleWin,struct GAMERULES* gameRules)
{
	clear();
	refresh();
	int key;
	int menuState=0;
	int highlight=0;
	int pathCount=0;
	char deckPath[64];
	char* deckPaths[10];
	strcpy(deckPath,"decks/");
	deckPaths[pathCount]=malloc(strlen(deckPath)*sizeof(char));
	strcpy(deckPaths[pathCount],deckPath);
	struct DIRECTORY decks;
	readDirectory(&decks,deckPath);
	while(menuState>=0)
	{
		mvwprintw((*titleWin),1,1,"Selected Deck:\n");
		mvwprintw((*titleWin),1,16,gameRules->DECK.NAME,"\n");
		wrefresh((*titleWin));
		wclear((*menuWin));
		int i=0;
		while(i<decks.SUBCOUNT)
		{
			if(i==highlight)
			{
				wattron((*menuWin),A_REVERSE);
			}
			mvwprintw((*menuWin),i+1,1,"%s%s%s","</",decks.SUB_DIRECTORIES[i],"/>");
			wattroff((*menuWin),A_REVERSE);
			i+=1;
		}
		for(int j=0;j<decks.FILECOUNT;j++)
		{
			if(j==highlight-i)
			{
				wattron((*menuWin),A_REVERSE);
			}
			mvwprintw((*menuWin),i+j+1,1,decks.FILES[j]);
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
				if(highlight==(decks.FILECOUNT+decks.SUBCOUNT)-1)
				{
					break;
				}else
				{
					highlight++;
					break;
				}
			case KEY_RIGHT:
				if(highlight<decks.SUBCOUNT)
				{
					strcat(deckPath,decks.SUB_DIRECTORIES[highlight]);
					strcat(deckPath,"/");
					pathCount+=1;
					deckPaths[pathCount]=malloc(32*sizeof(char));
					strcpy(deckPaths[pathCount],deckPath);
					readDirectory(&decks,deckPath);
					highlight=0;
					break;
				}else
				{
					strcpy(gameRules->DECK.NAME,decks.FILES[highlight-decks.SUBCOUNT]);
					strcat(deckPath,decks.FILES[highlight-decks.SUBCOUNT]);
					readDeck(&gameRules->DECK,deckPath);
					memset(deckPath,'\0',strlen(deckPath));
					strcpy(deckPath,deckPaths[pathCount]);
				}
				break;
			case KEY_LEFT:
				if(pathCount>0)
				{
					pathCount-=1;
					memset(deckPath,'\0',strlen(deckPath));
					strcpy(deckPath,deckPaths[pathCount]);
					readDirectory(&decks,deckPath);
					highlight=0;
				}else
				{
					menuState=-1;
				}
			default:
				break;
		}
	}
}


#endif
