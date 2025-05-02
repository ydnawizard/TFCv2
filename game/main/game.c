

void playGame(struct GAMERULES gameRules,char** playOpts)
{
	clear();
	refresh();
	int key;
	int gameState=0;
	int yMax, xMax;
	getmaxyx(stdscr,yMax,xMax);               
	WINDOW* questionWin=newwin(10,45,15,25);
	WINDOW* answerWin=newwin(3,67,25,25);
	WINDOW* rulesWin=newwin(10,22,15,70);
	wborder(questionWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(answerWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	wborder(rulesWin,ACS_VLINE,ACS_VLINE,ACS_HLINE,ACS_HLINE,ACS_ULCORNER,ACS_URCORNER,ACS_LLCORNER,ACS_LRCORNER);
	mvwprintw(rulesWin,1,1,playOpts[0]);
	mvwprintw(rulesWin,2,1,playOpts[2]);
	mvwprintw(rulesWin,3,1,playOpts[3]);
	mvwprintw(rulesWin,4,1,playOpts[4]);
	char c;
	int ticker=0;
	while(gameState>=0)
	{
		mvwprintw(questionWin,1,1,gameRules.DECK.CARDS[0].FRONT);
		mvwprintw(answerWin,1,1,"%c",c);
		wrefresh(questionWin);
		wrefresh(answerWin);
		wrefresh(rulesWin);
		if(kbhit())
		{
			c = wgetch(answerWin);
		}
		ticker+=1;
	}
}

