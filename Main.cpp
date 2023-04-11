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

		OffensiveStats* offStats = new OffensiveStats();
		DefensiveStats* defStats = new DefensiveStats();
		int rankCounter = 1, weight = 0, newHeight = 0;
		std::string name, position, school, height;

		while (getline(FILE, line)) {
			std::istringstream ss(line); // istringstream is more efficient
			//ss >> name >> position >> school >> height >> weight;
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

			//Player* player = new Player(rankCounter, name, position, school, newHeight, weight, offStats, defStats);
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
	for (auto player : players) {
		player->printInfo();
	}
}

void browseByPosition() {
	int choice;
	std::vector<std::string> offensive_positions{ "QB", "RB", "WR", "TE", "OT", "iOL" };
	std::vector<std::string> defensive_positions{ "EDGE", "DL", "LB", "CB", "S" };

	std::cout << "Would you like to browse by offense, defense, or specific position?" << std::endl;
	std::cout << "\t1. Offense" << std::endl;
	std::cout << "\t2. Defense" << std::endl;
	std::cout << "\t3. Specific position" << std::endl;
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

			std::cout << "What position would you like to browse?" << std::endl;
			std::cout << "\tValid positions: QB, RB, WR, TE, OT, iOL, EDGE, DL, LB, CB, S" << std::endl;
			std::cout << "\tPosition: ";

			if (std::cin >> posChoice) {
				std::vector<std::shared_ptr<Player>> matches;

				std::copy_if(players.begin(), players.end(), std::back_inserter(matches),
					[&posChoice](const std::shared_ptr<Player>& player) {
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
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl;
		std::cout << "Error: Please enter valid integer value" << std::endl;
	}
}

void browseBySchool() {
	std::string key;
	std::vector<std::shared_ptr<Player>> matches;

	std::cout << "Enter school (case-sensitive; start each word with caps): ";

	if (std::getline(std::cin, key)) {
		for (const auto& player : players) {
			if (player->getSchool() == key) {
				matches.push_back(player);
			}
		}
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl;
		std::cout << "Error: Please enter valid integer value" << std::endl;
	}

	std::cout << "RESULTS FOR " << key << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	if (!matches.empty()) {
		for (const auto match : matches) {
			match->printInfo();
		}
	}
	else {
		std::cout << "No schools matched your query of: " << key << std::endl;
	}
}

void playerViewer() {
	int choice;

	std::cout << "How would like to browse players?" << std::endl;
	std::cout << "\t1. Browse All" << std::endl;
	std::cout << "\t2. By Position" << std::endl;
	std::cout << "\t3. By School" << std::endl;
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

void menu() {
	int choice;

	std::cout << "Welcome to the 2023 NFL Draft" << std::endl;
	std::cout << "-----------------------------" << std::endl;
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

int main() {
	loadPlayers();

	menu();
}
