#ifndef PLAYMENU_H
#define PLAYMENU_H

char* playOpts[5]={"Deck","Orientation","Repeat","Timer","Back"};

void playMenu(WINDOW** menuWin,WINDOW** titleWin,struct GAMERULES* gameRules)
{
	clear();
	refresh();
	int key;
	int menuState=0;
	char tempState[8];
	int highlight=0;
	int currentMenu[2]={0,0};
	int pathCount=0;
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
