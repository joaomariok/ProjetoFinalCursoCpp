#include "Save.h"
using namespace std;
namespace fs = std::filesystem;

Save::Save() {
	directory_ = "C:/TrucoGame/";
	std::filesystem::create_directories(directory_);
}

bool Save::SaveGame(const Model& inputModel) {
	ofstream outFile(directory_ + "save.txt", std::ios::binary);

	if (!outFile.is_open())
	{
		std::cerr << "File could not be opened." << std::endl;
		return false;
	}

	char has_four_players = inputModel.GetHasFourPlayers() ? 1 : 0;
	Player player_one = *inputModel.GetPlayer(1);
	Player player_two = *inputModel.GetPlayer(2);
	int current_hand_round_number = inputModel.GetCurrentHandRoundNumber();

	outFile.write(reinterpret_cast<const char*>(&has_four_players), sizeof(has_four_players));

	SerializablePlayer s_player = player_one.SerializePlayer();
	outFile.write(reinterpret_cast<const char*>(&s_player), sizeof(SerializablePlayer));

	s_player = player_two.SerializePlayer();
	outFile.write(reinterpret_cast<const char*>(&s_player), sizeof(SerializablePlayer));

	if (inputModel.GetHasFourPlayers()) {
		Bot player_three = *static_cast<Bot*>(inputModel.GetPlayer(3));
		Bot player_four = *static_cast<Bot*>(inputModel.GetPlayer(4));

		s_player = player_three.SerializePlayer();
		outFile.write(reinterpret_cast<const char*>(&s_player), sizeof(SerializablePlayer));

		s_player = player_four.SerializePlayer();
		outFile.write(reinterpret_cast<const char*>(&s_player), sizeof(SerializablePlayer));
	}

	outFile.write(reinterpret_cast<const char*>(&current_hand_round_number), sizeof(current_hand_round_number));

	outFile.close();
	return true;
}

bool Save::LoadGame(Model* inputModel) {
	ifstream inFile(directory_ + "save.txt", std::ios::binary);

	if (!inFile.is_open()) {
		return false;
	}
	char has_four_players;
	Player player_one;
	Player player_two;
	Bot player_three;
	Bot player_four;
	int current_hand_round_number;
	SerializablePlayer s_player;

	inFile.read(reinterpret_cast<char*>(&has_four_players), sizeof(has_four_players));

	inFile.read(reinterpret_cast<char*>(&s_player), sizeof(SerializablePlayer));
	player_one.DeserializePlayer(s_player);

	inFile.read(reinterpret_cast<char*>(&s_player), sizeof(SerializablePlayer));
	player_two.DeserializePlayer(s_player);

	if (has_four_players) {
		inFile.read(reinterpret_cast<char*>(&s_player), sizeof(SerializablePlayer));
		player_three.DeserializePlayer(s_player);

		inFile.read(reinterpret_cast<char*>(&s_player), sizeof(SerializablePlayer));
		player_four.DeserializePlayer(s_player);
	}

	inFile.read(reinterpret_cast<char*>(&current_hand_round_number), sizeof(current_hand_round_number));

	inputModel->SetHasFourPlayers(has_four_players ? true : false);
	inputModel->SetPlayer(1, player_one);
	inputModel->SetPlayer(2, player_two);
	if (inputModel->GetHasFourPlayers()) {
		inputModel->SetPlayer(3, player_three);
		inputModel->SetPlayer(4, player_four);
	}
	inputModel->SetCurrentHandRoundNumber(current_hand_round_number);

	inFile.close();
	return true;
}

bool Save::ThereIsALoad()
{
	return fs::exists(directory_ + "save.txt");
}

Save::~Save() = default;


