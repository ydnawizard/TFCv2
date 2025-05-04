#include "main.h"

int main()
{
	struct GAMERULES gameRules;
	gameRules.CARD_TIMER=0;
	gameRules.GAME_TIMER=0;
	gameRules.SHUFFLE=false;
	gameRules.REPEAT=false;
	gameRules.ORIENTATION=1;
	gameRules.PLAY=0;
	int menuState=0;
	struct TXT test;
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	int yMax, xMax;
	getmaxyx(stdscr,yMax,xMax);
	WINDOW* titleWin=newwin(3,75,.30*yMax,.333*xMax);
	WINDOW* menuWin=newwin(20,35,.35*yMax,.333*xMax);
	keypad(menuWin,true);
	while(gameRules.PLAY>=0)
	{
		menu(&menuWin,&titleWin,&gameRules);
		playMenu(&menuWin,&titleWin,&gameRules);
		decksMenu(&menuWin,&titleWin,&gameRules);
		timerMenu(&menuWin,&titleWin,&gameRules);
	}

}
 
