#ifndef READDECK_H
#define READDECK_H


void readDeck(struct DECK* deck,char* deckName)
{
	deck->CARDS=(struct CARD*)malloc(sizeof(struct CARD));
	char deckPath[64]="/home/andy/proj/c/TFCv2/";
	strcat(deckPath,deckName);
	struct TXT txt;
	readTXT(&txt,deckPath);
	int cardCount;
	cardCount=0;
	for(int i=1;i<txt.LINE_COUNT;i+=2)
	{
		deck->CARDS=(struct CARD*)realloc(deck->CARDS,(cardCount+1)*sizeof(struct CARD));
		deck->CARDS[cardCount].FRONT=(char*)malloc(strlen(txt.LINES[i-1])*sizeof(char));
		deck->CARDS[cardCount].BACK=(char*)malloc(strlen(txt.LINES[i])*sizeof(char));
		strcpy(deck->CARDS[cardCount].FRONT,txt.LINES[i-1]);
		strcpy(deck->CARDS[cardCount].BACK,txt.LINES[i]);
		deck->CARDS[cardCount].ID=cardCount;
		cardCount+=1;
	}
	deck->CARD_COUNT=cardCount;
}


#endif
