#include "Save.h"

Save::Save() {
	directory_ = "C:/TrucoGame/";
	std::filesystem::create_directories(directory_);
}

bool Save::SaveGame(const Model& inputModel) {
	std::ofstream outFile(directory_ + "save.txt", std::ios::binary);

	if (!outFile.is_open())
	{
		std::cerr << "File could not be opened." << std::endl;
		return false;
	}

	char has_four_players = inputModel.GetHasFourPlayers() ? 1 : 0;
	Player player_one = *inputModel.GetPlayer(1);
	Player player_two = *inputModel.GetPlayer(2);
	Bot player_three;
	Bot player_four;

	if (inputModel.GetHasFourPlayers()) {
		player_three = *static_cast<Bot*>(inputModel.GetPlayer(3));
		player_four = *static_cast<Bot*>(inputModel.GetPlayer(4));
	}
	Deck deck = *inputModel.GetDeck();

	outFile.write(reinterpret_cast<const char*>(&has_four_players),
		sizeof(has_four_players));
	outFile.write(reinterpret_cast<const char*>(&player_one),
		sizeof(Player));
	outFile.write(reinterpret_cast<const char*>(&player_two),
		sizeof(Player));
	if (inputModel.GetHasFourPlayers()) {
		outFile.write(reinterpret_cast<const char*>(&player_three),
			sizeof(Player));
		outFile.write(reinterpret_cast<const char*>(&player_four),
			sizeof(Player));
	}
	outFile.write(reinterpret_cast<const char*>(&deck),
		sizeof(Deck));

	outFile.close();
	return true;
}

bool Save::LoadGame(Model& inputModel) {
	std::ifstream inFile(directory_ + "save.txt", std::ios::binary);

	if (!inFile.is_open()) {
		return false;
	}
	char has_four_players;
	Player player_one;
	Player player_two;
	Bot player_three;
	Bot player_four;

	inFile.read(reinterpret_cast<char*>(&has_four_players),
		sizeof(has_four_players));
	inFile.read(reinterpret_cast<char*>(&player_one),
		sizeof(Player));
	inFile.read(reinterpret_cast<char*>(&player_two),
		sizeof(Player));

	if (inputModel.GetHasFourPlayers()) {
		inFile.read(reinterpret_cast<char*>(&player_three),
			sizeof(Bot));
		inFile.read(reinterpret_cast<char*>(&player_four),
			sizeof(Bot));
	}

	Deck deck;
	inFile.read(reinterpret_cast<char*>(&deck), sizeof(Deck));

	inputModel.SetHasFourPlayers(has_four_players ? true : false);
	inputModel.SetPlayer(1, &player_one);
	inputModel.SetPlayer(2, &player_two);
	if (inputModel.GetHasFourPlayers()) {
		inputModel.SetPlayer(3, &player_three);
		inputModel.SetPlayer(4, &player_four);
	}
	inputModel.SetDeck(&deck);

	inFile.close();
	return true;
}

Save::~Save() = default;


