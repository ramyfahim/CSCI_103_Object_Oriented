#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
 public:
  Card();
  Card(char suit, int value);
  std::string toString();
  int compare(Card other);
 private:
  char _suit;
  int _value;

};

#endif
