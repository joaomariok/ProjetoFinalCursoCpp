#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Player
{
public:
	enum Group { NO_GROUP, GROUP_1, GROUP_2 };

	Player();
	Player(std::string inputName, Group group = Group::NO_GROUP, int playerNumber = 0);
	std::string GetName();
	int GetScore();
	int GetPlayerNumber(){ return playerNumber; }
	void IncreaseScore(int inputScore);
	std::vector<Card> GetHand();
	virtual void SetHand(std::vector<Card>& newHand);
	virtual Card PlayCard(int cardIndex);
	void SetGroup(Group group);
	Group GetGroup() const { return group_; }
	void ResetRoundScore() { round_score_ = 0; }
	void IncreaseRoundScore();
	int GetRoundScore() const { return round_score_; }

	virtual ~Player();
	/*void PrintHand();
	void Truco();*/

private:
	int playerNumber;
	std::string name_;
	int score_;
	int round_score_;
	std::vector<Card> hand_;
	Group group_;
};