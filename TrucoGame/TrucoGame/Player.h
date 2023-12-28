#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Player
{
private:
	std::string name;
	int score;
	std::vector<Card> hand;

public:
	Player(std::string inputName);
	std::string GetName();
	int GetScore();
	void IncreaseScore(int inputScore);
	std::vector<Card> GetHand();
	void SetHand(std::vector<Card>& newHand);

	/*void PrintHand();
	void Truco();*/
};