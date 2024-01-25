#pragma once
#include <string>

class Card
{
private:
	std::string value;
	std::string type;

public:
	Card(std::string inputValue, std::string inputType);

	enum Type { SPADES, HEARTS, DIAMONDS, CLUBS };
	enum Value { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

	std::string GetValue();

	std::string GetType();
};
