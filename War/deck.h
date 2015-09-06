#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck {
 public:
  Deck();
  void shuffle();
  void cut();
  Card getTop();
  void printDeck();
 private:
  Card _cards[52];
  int _topIndex;
};

#endif
