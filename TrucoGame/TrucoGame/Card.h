#pragma once
class Card
{
public:
	enum Suit { DIAMONDS, SPADES, HEARTS, CLUBS };
	enum Rank { FOUR, FIVE, SIX, SEVEN, QUEEN, JACK, KING, ACE, TWO, THREE };

	Card(Suit inputSuit, Rank inputRank);
	Card();
	Card(const Card& other) = default;
	Card(Card&& other) noexcept = default;
	Card& operator=(const Card& other) = default;
	Card& operator=(Card&& other) noexcept = default;
	~Card();

	Suit GetSuit() const;
	Rank GetRank() const;

	bool IsZap() const;
	void SetIsManilha();
	bool IsManilha() const;
	bool IsBiggerThan(Card card) const;

private:
	Suit suit_;
	Rank rank_;
	bool is_manilha_;
};
