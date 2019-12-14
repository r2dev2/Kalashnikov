#include "Kalashnikov.h"

int garbagesize = 1;
int shelfsize = 1;
int discardsize = 1;

int main(){
	Card *cardDeck = createDeck();
	Card **garbage = createPile(&cardDeck);
	garbage = addToPile(garbage, cardDeck+1, 1);
	dispPile(garbage, 1);
	printf("%d\n", garbagesize);
	garbage = removeFromPile(garbage, cardDeck+1, 1);
	dispPile(garbage, 1);
	printf("%d\n", garbagesize);
	return 0;
}

Card *createDeck(){
	static Card deck[52];
	int s = 0;
	for (int i = 0; i<52; i++){
		int n = (i%13) + 1;
		if (i%13 == 0){
			s += 1;
		}
		deck[i].number = n;
		deck[i].suit = s;
	}
	return deck;
}

Card **createPile(Card **d){
	Card **temp = (Card**) malloc(sizeof(Card*));
	*temp = *d;
	return temp;
}

Card **addToPile(Card **p, Card *c, int pilenum){
	int s;
	switch (pilenum){
		case 1:
			s = garbagesize;
			garbagesize += 1;
			break;
		
		case 2:
			s = shelfsize;
			shelfsize += 1;
			break;
		
		case 3:
			s = discardsize;
			discardsize += 1;
			break;
	}
	s += 1;
	Card **temp =  (Card **) malloc(s*sizeof(Card*));
	for (int i = 0; i<s; i++){
		if (i == s-1){
			*(temp+i) = c;
			continue;
		}
		*(temp+i) = *(p+i);
	}
	free(p);
	return temp;
}

Card **removeFromPile(Card **p, Card *c, int pilenum){
	int s, reached;
	int tempidx = 0;
	switch (pilenum){
		case 1:
			s = garbagesize;
			garbagesize -= 1;
			break;
		
		case 2:
			s = shelfsize;
			shelfsize -= 1;
			break;
		
		case 3:
			s = discardsize;
			discardsize -= 1;
			break;
	}
	Card **temp = (Card**) malloc((s-1) * sizeof(Card*));
	/*while (temp == NULL){
		temp = (Card**) malloc((s-1) * sizeof(Card*));
	}*/
	if (temp == NULL){
		printf("Malloc failed.\n");
		exit(11);
	}
	for (int i = 0; i<s; i++){
		if (*(p+i) == c){
			reached = 1;
			continue;
		}
		if (reached == 0 && i == s-1){
			printf("Card not present");
			exit(11);
		}
		*(temp+tempidx) = *(p+i);
		tempidx++;
	}
	free(p);
	return temp;
}

void dispCard(Card *c){
	int n = (*c).number;
	int s = (*c).suit;
	switch (n){
		case 11:
			printf("Jack");
			break;
		case 12:
			printf("Queen");
			break;
		case 13:
			printf("King");
			break;
		case 1:
			printf("Ace");
			break;
		default:
			printf("%d", n);
			break;
	}
	switch (s){
		case 1:
			printf(" of Clubs");
			break;
		case 2:
			printf(" of Spades");
			break;
		case 3:
			printf(" of Hearts");
			break;
		case 4:
			printf(" of Diamonds");
			break;
	}
	printf("\n");
}

void dispPile(Card **p, int pilenum){
	int s;
	switch (pilenum){
		case 1:
			s = garbagesize;
			break;
		
		case 2:
			s = shelfsize;
			break;
		
		case 3:
			s = discardsize;
			break;
	}
	for (int i = 0; i<s; i++){
		dispCard(*(p+i));
	}
}