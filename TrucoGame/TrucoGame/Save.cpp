#include "Save.h"

Save::Save() {
	directory_ = "C:/TrucoGame/";
	std::filesystem::create_directories(directory_);
}

int Save::SaveGame(const Model& inputModel) {
	try {
		std::ofstream outFile(directory_ + "save.txt", std::ios::binary);

		if (!outFile.is_open())
		{
			return 5;
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

		outFile.write(reinterpret_cast<const char*>(&has_four_players),
			sizeof(has_four_players));
		outFile.write(reinterpret_cast<const char*>(&player_one),
			sizeof(Player));
		outFile.write(reinterpret_cast<const char*>(&player_two),
			sizeof(Player));
		if (inputModel.GetHasFourPlayers()) {
			outFile.write(reinterpret_cast<const char*>(&player_three),
				sizeof(Bot));
			outFile.write(reinterpret_cast<const char*>(&player_four),
				sizeof(Bot));
		}

		outFile.close();
		return 1;
	}
	catch (const std::ios_base::failure& e) {
		std::cerr << "Erro de E/S: " << e.what() << std::endl;
		return 2;
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Erro de alocação de memória: " << e.what() << std::endl;
		return 3;
	}
	catch (const std::bad_cast& e) {
		std::cerr << "Erro de conversão de tipo: " << e.what() << std::endl;
		return 4;
	}
	catch (const std::exception& e) {
		std::cerr << "Erro genérico: " << e.what() << std::endl;
		return 0;
	}
}

int Save::LoadGame(Model& inputModel) {
	try {
		std::ifstream inFile(directory_ + "save.txt", std::ios::binary);

		if (!inFile.is_open()) {
			return 5;
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

		inputModel.SetHasFourPlayers(has_four_players ? true : false);
		inputModel.SetPlayer(1, player_one);
		inputModel.SetPlayer(2, player_two);
		if (inputModel.GetHasFourPlayers()) {
			inputModel.SetPlayer(3, player_three);
			inputModel.SetPlayer(4, player_four);
		}

		inFile.close();
		return 1;
	}
	catch (const std::ios_base::failure& e) {
		std::cerr << "Erro de E/S: " << e.what() << std::endl;
		return 2;
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Erro de alocação de memória: " << e.what() << std::endl;
		return 3;
	}
	catch (const std::bad_cast& e) {
		std::cerr << "Erro de conversão de tipo: " << e.what() << std::endl;
		return 4;
	}
	catch (const std::exception& e) {
		std::cerr << "Erro genérico: " << e.what() << std::endl;
		return 0;
	}
}

Save::~Save() = default;


