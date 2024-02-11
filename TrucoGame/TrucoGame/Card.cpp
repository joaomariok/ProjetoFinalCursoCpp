#include "Card.h"

Card::Card(Suit inputSuit, Rank inputRank) :
	suit_(inputSuit), rank_(inputRank), is_manilha_(false) {}

Card::Card() :
	suit_(Suit::SPADES), rank_(Rank::ACE), is_manilha_(false) {}

Card::~Card() = default;

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
