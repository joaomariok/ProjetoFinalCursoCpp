#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Model.h"
#include "Player.h"
#include "Deck.h"

class Save
{
public:
	Save(std::string inputDirectory);
	~Save();
	bool SaveGame(const Model &inputModel);
	bool LoadGame(Model& inputModel);

private:
	std::string directory_;
};
