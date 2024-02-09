#pragma once
#include <string>

class Card
{
public:
	enum Suit { SPADES, HEARTS, DIAMONDS, CLUBS };
	enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, JACK, QUEEN, KING, ACE };

	Card(Suit inputSuit, Rank inputRank);
	Card();
	~Card();

	Suit GetSuit() const;
	Rank GetRank() const;

private:
	Suit suit_;
	Rank rank_;
};
