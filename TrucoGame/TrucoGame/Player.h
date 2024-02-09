#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Player
{
public:
	Player();
	Player(std::string inputName);
	std::string GetName();
	int GetScore();
	void IncreaseScore(int inputScore);
	std::vector<Card> GetHand();
	void SetHand(std::vector<Card>& newHand);
	Card PlayCard();

	/*void PrintHand();
	void Truco();*/

private:
	std::string name_;
	int score_;
	int round_score_;
	std::vector<Card> hand_;
};