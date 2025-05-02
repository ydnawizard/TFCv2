#ifndef DECK_H
#define DECK_H

struct DECK
{
	char NAME[64];
	struct CARD* CARDS;
	int CARD_COUNT;
	int AVG_TIME;
	float AVG_CORRECT;
};

#endif
