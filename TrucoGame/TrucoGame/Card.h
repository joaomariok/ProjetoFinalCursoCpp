#pragma once
#include <string>

class Card
{
public:
	enum Suit { SPADES, HEARTS, DIAMONDS, CLUBS };
	enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, JACK, QUEEN, KING, ACE };

	Card(Suit inputSuit, Rank inputRank);
	Card();
	Card(const Card& other) = default;
	Card(Card&& other) noexcept = default;
	Card& operator=(const Card& other) = default;
	Card& operator=(Card&& other) noexcept = default;
	~Card();

	Suit GetSuit() const;
	Rank GetRank() const;

private:
	Suit suit_;
	Rank rank_;
};
