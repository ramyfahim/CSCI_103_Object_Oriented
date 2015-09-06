#include <iostream>
#include <sstream>
#include "card.h"
using namespace std;

const char* cardVals[] = {"2","3","4", "5", "6", "7", "8", 
		  "9", "10", "J", "Q", "K", "A"};

Card::Card()
{
  _suit = 'C';
  _value = 0;
}

Card::Card(char suit, int value)
{
  _suit = suit;
  _value = value;
}

string Card::toString()
{

	stringstream ss;
	ss << cardVals[_value] << "-" << _suit;
	string text = ss.str();
	return text;


}

int Card::compare(Card other)
{
  if(_value < other._value){
    return -1;
  }
  else if(_value > other._value){
    return 1;
  }
  else {
    return 0;
  }
}
