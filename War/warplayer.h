#ifndef WARPLAYER_H
#define WARPLAYER_H

#include "card.h"

class WarPlayer
{
 public: 
  WarPlayer();
  void addCard(Card c);
  Card removeTopCard();

  // Add your two functions here
bool sizecheck();
int value();


 private:
  Card _cards[52];
  int _head;
  int _tail;
  int _size;

};

#endif
