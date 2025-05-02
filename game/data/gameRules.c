#ifndef GAMERULES_H
#define GAMERULES_H

struct GAMERULES
{
	struct DECK DECK;
	int ORIENTATION; //1 - front, 0 - back
	bool REPEAT;
	bool SHUFFLE;
	int CARD_TIMER;
	int GAME_TIMER;
};

#endif
