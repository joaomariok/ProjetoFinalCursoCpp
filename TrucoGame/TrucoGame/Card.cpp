#include "Card.h"

Card::Card(Suit inputSuit, Rank inputRank) :
	suit_(inputSuit), rank_(inputRank) {}

Card::Card() :
	suit_(Suit::SPADES), rank_(Rank::ACE) {}

Card::~Card() = default;

Card::Suit Card::GetSuit() const {
	return suit_;
}

Card::Rank Card::GetRank() const {
	return rank_;
}
