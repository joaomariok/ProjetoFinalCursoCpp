#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Player
{
public:
	enum Group { NO_GROUP, GROUP_1, GROUP_2 };

	Player();
	Player(std::string inputName, Group group = Group::NO_GROUP);
	std::string GetName();
	int GetScore();
	void IncreaseScore(int inputScore);
	std::vector<Card> GetHand();
	void SetHand(std::vector<Card>& newHand);
	Card PlayCard(int cardIndex);
	void SetGroup(Group group);
	Group GetGroup() const { return group_; }
	void IncreaseRoundScore();
	int GetRoundScore() const { return round_score_; }

	virtual ~Player();
	/*void PrintHand();
	void Truco();*/

private:
	std::string name_;
	int score_;
	int round_score_;
	std::vector<Card> hand_;
	Group group_;
};