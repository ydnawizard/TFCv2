#include "main.h"

int main()
{
	struct GAMERULES gameRules;
	struct TXT test;
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	int yMax, xMax;
	getmaxyx(stdscr,yMax,xMax);
	WINDOW* titleWin=newwin(3,75,.31*yMax,.333*xMax);
	WINDOW* menuWin=newwin(20,35,.333*yMax,.333*xMax);
	keypad(menuWin,true);
	menu(&menuWin,&titleWin,&gameRules);
}
 
