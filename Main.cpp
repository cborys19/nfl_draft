#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Player.h"
#include "Stats.h"

std::vector<std::shared_ptr<Player>> players;

// function to convert string height representation to int
int heightParser(const std::string& height) {
	int feet, inches;
	std::istringstream strstm(height);
	char dash;
	strstm >> feet >> dash >> inches;
	return ((feet * 12) + inches);
}

void loadPlayers() {
	std::fstream FILE;
	FILE.open("players.txt", std::ios::in);
	if (!FILE.is_open()) {
		std::cout << "players.txt COULD NOT BE FOUND" << std::endl;
		std::cout << "Sorry!" << std::endl;
		exit(-1);
	}		
	else {
		std::string line;

		int rankCounter = 1, weight = 0, newHeight = 0;
		std::string name, position, school, height;

		while (getline(FILE, line)) {
			std::istringstream ss(line); // istringstream is more efficient
			std::string value;
			bool isName = true;

			while (getline(ss, value, ',')) {
				try {
					// Try block to test if value is completely an integer
					// If an exception is NOT thrown, the value will be stored as the player's weight

					if (value[1] != '-') // Test to differentiate between height and weight
						weight = stoi(value);
					else // Value is not currently the weight
						throw std::invalid_argument(""); 
				}
				catch (...) {
					if (value == "QB" || value == "RB" || value == "WR" || value == "TE" ||
						value == "iOL" || value == "OT" || value == "EDGE" || value == "DL" ||
						value == "CB" || value == "S" || value == "LB") { // Test if value = position
						position = value;
					}
					else if (value[1] == '-') { // Test if value = height
						newHeight = heightParser(value);
					}
					else if (isName) { // Test if value is name
						/*
							The first string value that will be read is the player's name, then their
							school. Since this is a constant order, we can set a boolean flag to
							switch between true and false whenever one of these is read since the
							next one to be read will always be different (i.e. if name is read, then
							the next string is guaranteed to be the school, and vice-versa)
						*/

						name = value;
						isName = !isName;
					}
					else {
						school = value;
						isName = !isName;
					}
				}				
			}

			std::optional<std::shared_ptr<OffensiveStats>> offStats = std::make_shared<OffensiveStats>();
			std::optional<std::shared_ptr<DefensiveStats>> defStats = std::make_shared<DefensiveStats>();
			players.push_back(std::make_shared<Player>(rankCounter, name, position, school, newHeight, weight, offStats, defStats));
			rankCounter += 1;
		}

		FILE.close();
	}
		
}

void draft() {
	std::cout << "Draft" << std::endl;
}

void browseAll() {
	for (const auto& player : players) {
		player->printInfo();
	}
}

void browseByPosition() {
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

				for (const auto& player : players) {
					auto it = std::find(offensive_positions.begin(), offensive_positions.end(),
						player->getPosition());
					if (it != offensive_positions.end()) {
						player->printInfo();
					}
				}
			}
			else if (choice == 2) {
				// Searches the players vector for all players with a defensive position

				for (const auto& player : players) {
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
					std::copy_if(players.begin(), players.end(), std::back_inserter(matches),
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

void browseBySchool() {
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
				for (const auto& player : players) {
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

void playerViewer() {
	int choice;
	bool runFlag = true;
	while (runFlag) {
		std::cout << "How would like to browse players?" << std::endl;
		std::cout << "\t1. Browse All" << std::endl;
		std::cout << "\t2. By Position" << std::endl;
		std::cout << "\t3. By School" << std::endl;
		std::cout << "\t9. Back to Main Menu" << std::endl;
		std::cout << "\tSelect Option: ";

		if (std::cin >> choice) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			switch (choice) {
			case 1:
				browseAll();
				break;
			case 2:
				browseByPosition();
				break;
			case 3:
				browseBySchool();
				break;
			case 9:
				return;
			default:
				std::cout << "Please select a valid option" << std::endl;
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

void mainMenu() {
	int choice;
	bool runFlag = true;

	std::cout << "Welcome to the 2023 NFL Draft!" << std::endl;
	//std::cout << "-----------------------------" << std::endl;
	while (runFlag) {
		std::cout << "\n\tMAIN MENU" << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << "Please select what you wish to do" << std::endl;
		std::cout << "\t1. Begin Draft" << std::endl;
		std::cout << "\t2. Browse Players" << std::endl;
		std::cout << "\t9. Exit" << std::endl << std::endl;
		std::cout << "\tSelect Option: ";

		if (std::cin >> choice) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			switch (choice) {
			case 1:
				draft();
				break;
			case 2:
				playerViewer();
				break;
			case 9:
				std::cout << "Thanks for joining us. Exiting..." << std::endl;
				exit(-1);
			default:
				std::cout << "Please select a valid option" << std::endl;
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

int main() {
	loadPlayers();

	mainMenu();
}
