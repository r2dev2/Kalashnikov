#include "Kalashnikov.h"

int garbagesize = 0;
int shelfsize = 0;
int discardsize = 0;
int ac;

Card *deck;
Card **garbage;
Card **shelf;
Card **discard;

Player boris, vadim;

int main(int argc, char* argv[]){
	ac = argc;
	srand(time(NULL));
	deck = createDeck();
	garbage = createPile(deck);
	garbage = (Card**) initGarbage(garbage, deck);
	// dispPile(garbage, 1);
	// printf("%d\n",garbagesize);
	int *ognums = (int *) malloc(52 * sizeof(int));
	for (int i = 0; i<52; i++){
		*(ognums+i) = i+1;
	}
	// printf("Created\n");
	shuffle(ognums, 52);
	// printf("Shuffled %d\n", *ognums);
	Player *b = createPlayer(ognums);
	Player *v = createPlayer(ognums+4);
	// printf("Player created\n");
	// printf("%d\n",garbagesize);
	// printf("%d\n",isKalashnikov(b));

	// Actual round
	int cardidx;
	Player *currplayer;
	Player *opponentplayer;
	int turn = 0;
	char *playername;
	while (b->health > 0 && v->health > 0){
		if (argc == 1){
			for (int i = 0; i<20; i++){
				printf("\n\n");
			}
		}
		playername = (turn%2 == 0) ? "King Boris": "Vadim Blyat";
		currplayer = (turn%2 == 0) ? b:v;
		opponentplayer = (turn%2 == 0) ? v:b;
		writeToFile(currplayer->hand);
		printf("Current Player: %s Health: %d ", playername, currplayer->health);
		printNewLine();
		cardidx = userPromptSwapCard(currplayer);
		printf("Your card index to be swapped was %d. ", cardidx);
		printNewLine();
		if (cardidx == 5){
			currplayer->health = 0;
			printf("%s, what a debil.\n", playername);
			continue;
		}
		getFromPlayer(currplayer, cardidx);
		givePlayer(currplayer, cardidx, rand()%garbagesize);
		if (isKalashnikov(currplayer)==1){
			opponentplayer->health = opponentplayer->health - 20;
			printf("%s built his Kalashnikov\n", playername);
		}
		printf("\n");
		turn++;
	}
	char *victor = (v->health == 0) ? "King Boris": "Vadim Blyat";
	char strvictor[50];
	sprintf(strvictor, "\n%s was the victor.\n", victor);
	FILE *fp;
	fp = fopen("move.txt", "w+");
	fputs(strvictor, fp);
	fclose(fp);
	printf("%s was the victor.\n", victor);
	return 0;
}

void writeToFile(Card **p){
	char move[100];
	for (int i = 0; i < 4; i++){
		sprintf(move, "%s\n(%d,%d)", move, (**(p+i)).number, (**(p+i)).suit);
	}
	FILE *fp;
	fp = fopen("move.txt", "w+");
	fputs(move, fp);
	fclose(fp);
}

void printNewLine(){
	if (ac == 1){
		printf("\n");
	}
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

Card **createPile(){
	Card **temp = (Card**) malloc(sizeof(Card*));
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
	if (temp == NULL){
		exit(11);
	}
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
	// Throwing an error, TODO fix later
	/*if (p != NULL){
		free(p);
	}*/
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
	printf(" ");
	printNewLine();
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
		case 4:
			s = 4;
	}
	for (int i = 0; i<s; i++){
		dispCard(*(p+i));
	}
}

Card **initGarbage(Card **p, Card *d){
	for (int i = 0; i<52; i++){
		if (i==0){
			*p = d;
			garbagesize = 1;
			continue;
		}
		p = addToPile(p, d+i, 1);
	}
	garbagesize = 52;
	return p;
}

void givePlayer(Player *p, int pindx, int num){
	p->hand[pindx] = *(garbage + num);
	garbage = removeFromPile(garbage, *(garbage + num), 1);
}

void shuffle(int *array, size_t n){
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

// Commented out part tests if Kalashnikov detector works
Player *createPlayer(int *nums){
	Player *pl;
	//int n[] = {12,6,3,0};
	pl = &boris;
	if (pl->health == 20){
		pl = &vadim;
	}
	pl->health = 20;
	for (int i = 0; i<4; i++){
		givePlayer(pl, i, *(nums+i));
		//givePlayer(pl, i, *(n+i));
	}
	return pl;
}

void getFromPlayer(Player *p, int pindx){
	if (discardsize == 0){
		discard = createPile();
		discardsize = 1;
		*discard = p->hand[pindx];
	} else {
		discard = addToPile(discard, p->hand[pindx], 2);
	}
	p->hand[pindx] = NULL;
}

int userPromptSwapCard(Player *p){
	int idx;
	printf("Your hand currently has 4 cards: ");
	printNewLine();
	dispPile(p->hand, 4);
	printf("Which Card would you like to swap (int from 0-4)\n");
	// if (ac == 1){
	// 	printf("\n");
	// }
	scanf("%d", &idx);
	return idx;
}

int isKalashnikov(Player *p){
	int ace = 0;
	int king = 0;
	int four = 0;
	int seven = 0;
	int s;
	for (int i = 0; i<4; i++){
		s = (*(p->hand[i])).number;
		switch (s){
			case 1:
				ace = 1;
				break;
			case 13:
				king = 1;
				break;
			case 4:
				four = 1;
				break;
			case 7:
				seven = 1;
				break;
			default:
				break;
		}
	}
	return (ace+king+four+seven) == 4;
}
