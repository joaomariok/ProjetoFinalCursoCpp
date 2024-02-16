#include "Card.h"

Card::Card(Suit suit, Rank rank) :
	suit_(suit), rank_(rank), is_manilha_(false), is_hidden_(false) {}

Card::Card() : Card(Suit::SPADES, Rank::ACE) {}

Card::~Card() = default;

bool Card::operator==(const Card& other) const {
	return GetRank() == other.GetRank() && GetSuit() == other.GetSuit();
}

Card::Suit Card::GetSuit() const {
	return suit_;
}

Card::Rank Card::GetRank() const {
	return rank_;
}

void Card::SetIsManilha() {
	is_manilha_ = true;
}

bool Card::IsManilha() const {
	return is_manilha_;
}

void Card::SetIsHidden(bool is_hidden) {
	is_hidden_ = is_hidden;
}

bool Card::IsHidden() const {
	return is_hidden_;
}

bool Card::IsZap() const {
	return is_manilha_ && suit_ == Suit::CLUBS;
}

bool Card::IsBiggerThan(Card card) const {
	// The two compared cards are "Manilha" or have the same rank
	if (IsManilha() && card.IsManilha() || GetRank() == card.GetRank())
		return GetSuit() > card.GetSuit();

	// Only one card is "Manilha"
	if (IsManilha() || card.IsManilha())
		return IsManilha();

	return GetRank() > card.GetRank();
}
