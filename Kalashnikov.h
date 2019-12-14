#include <stdio.h>
#include <stdlib.h>

/*  Ace is 1, Jack is 11, Queen is 12, King is 13
    Clubs is 1, Spades is 2, Hearts is 3, Diamonds is 4  */
typedef struct {
	int suit;
	int number;
}Card;

typedef struct {
    int health;
    Card hand[4];
}Player;

/*extern Card deck[52];
extern Card *militaryGarbage[];
extern Card *shelf[];
extern Card *discard[];*/
extern int garbagesize, shelfsize, discardsize;

// garbage is pile 1, shelf is pile 2, discard is pile 3
Card *createDeck();
Card **createPile(Card **d);

Card **addToPile(Card **p, Card *c, int pilenum);
Card **removeFromPile(Card **p, Card *c, int pilenum);

void dispCard(Card *c);
void dispPile(Card **p, int pilenum);