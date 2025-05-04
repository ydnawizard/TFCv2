char* mainMenu[6]={"Play","Deck Builder","Client Settings","Stats","Info","Quit\n"};

void menu(WINDOW** menuWin,WINDOW** titleWin,struct GAMERULES* gameRules)
{
	clear();
	refresh();
	int key;
	char tempState[8];
	int highlight=0;
	int currentMenu[2]={0,0};
	int pathCount=0;
	while((*gameRules).PLAY==0)
	{
		wclear((*titleWin));
		mvwprintw((*titleWin),1,1,"Terminal Flash Cards v2.0\n");
		wrefresh((*titleWin));
		wclear((*menuWin));
		for(int i=0;i<6;i++)
		{
			if(i==highlight)
			{
				wattron((*menuWin),A_REVERSE);
			}
			mvwprintw((*menuWin),i+1,1,mainMenu[i]);
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
					(*gameRules).PLAY=1;
					playMenu(&(*menuWin),&(*titleWin),&(*gameRules));
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
			default:
				break;
		}
	}
}

