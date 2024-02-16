#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Model.h"
#include "Bot.h"
#include "Deck.h"

class Save
{
public:
	struct PlayerSave {
		std::string name_;
		int player_num_;
		int score_;
	};

	Save();
	~Save();
	int SaveGame(const Model &inputModel);
	int LoadGame(Model* inputModel);
	bool ThereIsALoad();

private:
	std::string directory_;
};
