#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int *array, size_t n);

/*  Ace is 1, Jack is 11, Queen is 12, King is 13
    Clubs is 1, Spades is 2, Hearts is 3, Diamonds is 4  */
typedef struct {
	int suit;
	int number;
}Card;

typedef struct {
    int health;
    Card *hand[4];
}Player;

extern Card *deck;
extern Card **garbage;
extern Card **shelf;
extern Card **discard;
extern int garbagesize, shelfsize, discardsize;
extern Player boris, vadim;

// garbage is pile 1, shelf is pile 2, discard is pile 3
Card *createDeck();
Card **createPile();
Card **initGarbage(Card **p, Card *d);

Card **addToPile(Card **p, Card *c, int pilenum);
Card **removeFromPile(Card **p, Card *c, int pilenum);

void dispCard(Card *c);
void dispPile(Card **p, int pilenum);

Player *createPlayer(int *nums);
void givePlayer(Player *p, int pindx, int num);
void getFromPlayer(Player *p, int pindx);

int userPromptSwapCard(Player *p);
int isKalashnikov(Player *p);