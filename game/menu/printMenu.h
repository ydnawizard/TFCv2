#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

char* menuNames[5]={"TERMINAL FLASH CARDS v2.0","GAME SETTINGS","CLIENT SETTINGS","STATS","INFO"};


char* blankOpts[1]={" "};
char* mainOpts[5]={"Play","Client Settings","Stats","Info","Quit"};
char* playOpts[5]={"Deck","Orientation","Repeat","Shuffle","Timer"};
char* settingsOpts[2]={"Theme","Animations"};
char* timerOpts[3]={"10","20","30"};

char** mainMenus[1]={mainOpts};
char** playMenus[2]={playOpts,timerOpts};
char** settingsMenus[1]={settingsOpts};


char*** menus[3]={mainMenus,playMenus,settingsMenus};

const int mainOptsCount=5;
const int playOptsCount=5;
const int settingsOptsCount=2;
const int timerOptsCount=3;

const int mainCounts[1]={mainOptsCount};
const int playCounts[2]={playOptsCount,timerOptsCount};
const int settingsCounts[1]={settingsOptsCount};

const int* menuCounts[3]={mainCounts,playCounts,settingsCounts};



void printTitle(WINDOW** titleWin,int* currentMenu)
{
	mvwprintw((*titleWin),1,1,menuNames[currentMenu[0]]);
	wrefresh((*titleWin));
}



void printMenu(WINDOW** menuWin,int* currentMenu,int highlight)
{
	wclear((*menuWin));
	for(int i=0;i<menuCounts[currentMenu[0]][currentMenu[1]];i++)
	{
		if(i==highlight)
		{
			wattron((*menuWin),A_REVERSE);
		}
		mvwprintw((*menuWin),i+1,1,menus[currentMenu[0]][currentMenu[1]][i]);
		wattroff((*menuWin),A_REVERSE);
	}
	wrefresh((*menuWin));
}

#endif
