#ifndef READCARD_H
#define READCARD_H

struct CARD* readCard(char* front,char* back,int id)
{
	struct CARD* card=(struct CARD*)malloc(sizeof(struct CARD));
	card->FRONT=(char*)malloc(strlen(card->FRONT)*sizeof(char));
	card->BACK=(char*)malloc(strlen(card->BACK)*sizeof(char));
	card->ID=id;
	strcpy(card->FRONT,front);
	strcpy(card->BACK,back);
	return card;
}

#endif
