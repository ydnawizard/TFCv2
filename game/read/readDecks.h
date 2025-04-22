#ifndef READECKS_H
#define READECKS_H

void readDecks(struct DIRECTORY* decks)
{
	readDirectory(&(*decks),"decks");
}

#endif
