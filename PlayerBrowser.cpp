#include "PlayerBrowser.h"

void PlayerBrowser::browseAll() {
	std::cout << "hello" << std::endl;
	for (const auto& player : playerObj.m_players) {
		player->printInfo();
	}
}

void PlayerBrowser::browseByPosition() {
	int choice;
	bool runFlag = true;
	const std::vector<std::string> offensive_positions{ "QB", "RB", "WR", "TE", "OT", "iOL" };
	const std::vector<std::string> defensive_positions{ "EDGE", "DL", "LB", "CB", "S" };

	while (runFlag) {
		std::cout << "Would you like to browse by offense, defense, or specific position?" << std::endl;
		std::cout << "\t1. Offense" << std::endl;
		std::cout << "\t2. Defense" << std::endl;
		std::cout << "\t3. Specific position" << std::endl;
		std::cout << "\t9. Back to Player Browsing Menu" << std::endl;
		std::cout << "\tSelect Option: ";

		if (std::cin >> choice) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;

			if (choice == 1) {
				// Searches the players vector for all players with an offensive position

				for (const auto& player : playerObj.m_players) {
					auto it = std::find(offensive_positions.begin(), offensive_positions.end(),
						player->getPosition());
					if (it != offensive_positions.end()) {
						player->printInfo();
					}
				}
			}
			else if (choice == 2) {
				// Searches the players vector for all players with a defensive position

				for (const auto& player : playerObj.m_players) {
					auto it = std::find(defensive_positions.begin(), defensive_positions.end(),
						player->getPosition());
					if (it != defensive_positions.end()) {
						player->printInfo();
					}
				}
			}
			else if (choice == 3) {
				// Prompts the user for a position to search by, searches the players vector for all
				// players that match that position, loads those players into vector of matches, then
				// returns each match to the user on-screen

				std::string posChoice;
				const std::string back = "BACK";

				std::cout << "What position would you like to browse?" << std::endl;
				std::cout << "\tValid positions: QB, RB, WR, TE, OT, iOL, EDGE, DL, LB, CB, S" << std::endl;
				std::cout << "\tEnter \"back\" to go back to Player Browsing Menu (case-insensitive)" << std::endl;
				std::cout << "\tPosition: ";

				if (std::cin >> posChoice) {
					// convert entered value to uppercase so that valid uppercase values are not affected
					std::transform(posChoice.begin(), posChoice.end(), posChoice.begin(), std::toupper);
					if (posChoice.compare(back) == 0) {
						return;
					}

					std::vector<std::shared_ptr<Player>> matches;
					std::copy_if(playerObj.m_players.begin(), playerObj.m_players.end(), std::back_inserter(matches),
						[&posChoice](const auto& player) {
							return player->getPosition() == posChoice;
						});

					for (const auto& match : matches) {
						match->printInfo();
					}
				}
				else {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << std::endl;
					std::cout << "Error: Please enter valid integer value" << std::endl;
				}
			}
			else if (choice == 9) {
				return;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
			std::cout << "Error: Please enter valid integer value" << std::endl;
		}
	}
}

void PlayerBrowser::browseBySchool() {
	// Currently uses a linear case-sensitive search to find players belonging to a given school
	std::string key;
	const std::string back = "BACK";
	bool runFlag = true;
	std::vector<std::shared_ptr<Player>> matches;

	while (runFlag) {
		std::cout << "Enter \"back\" to go back (case-insensitive)" << std::endl;
		std::cout << "Enter school (case-sensitive; start each word with caps): ";

		if (std::getline(std::cin, key)) {
			if (key.size() == back.size() &&
				std::equal(key.begin(), key.end(), back.begin(), [](char a, char b) -> bool {
					return std::toupper(static_cast<unsigned char>(a)) == std::toupper(static_cast<unsigned char>(b));
					})) {
				// case-insensitive check if user entered "back"
				return;
			}
			else {
				for (const auto& player : playerObj.m_players) {
					if (key.size() == player->getSchool().size() &&
						std::equal(key.begin(), key.end(), player->getSchool().begin(),
							[](char a, char b) -> bool {
								return std::toupper(static_cast<unsigned char>(a)) == std::toupper(static_cast<unsigned char>(b));
							})) {
						matches.push_back(player);
					}
				}
				runFlag = false;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl;
			std::cout << "Error: Please enter valid integer value" << std::endl;
		}
	}

	if (!matches.empty()) {
		std::cout << "RESULTS FOR " << key << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		for (const auto& match : matches) {
			match->printInfo();
		}
	}
	else {
		std::cout << "No schools matched your query of: " << key << std::endl;
	}
}

//void PlayerBrowser::sortBySchool() {
//
//}
//
//void PlayerBrowser::sortByHeight() {
//
//}
//
//void PlayerBrowser::sortByWeight() {
//
//}
//
//void PlayerBrowser::sortByPosition() {
//
//}
//
//void PlayerBrowser::search(std::string& key) {
//
//}