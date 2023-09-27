#include <iostream>
#include <string>
#include <optional>
#include <cstdio>

#include "Player.h"

Player::Player() {
	loadPlayers();
}

// Add stats once constructors for Stats class are outlined
Player::Player(int rank, std::string name, std::string position,
	std::string school, int height, int weight, 
	std::optional<std::shared_ptr<OffensiveStats>> offStats,
	std::optional<std::shared_ptr<DefensiveStats>> defStats) :
	m_rank(rank), 
	m_name(name),
	m_position(position),
	m_school(school),
	m_height(height),
	m_weight(weight),
	m_offStats(offStats),
	m_defStats(defStats) {}


int Player::getRank() const { return this->m_rank; }

void Player::setRank(int rank) { this->m_rank = rank; }

std::string Player::getName() const { return this->m_name; }

void Player::setName(std::string name) { this->m_name = name; }

std::string Player::getPosition() const { return this->m_position; }

void Player::setPosition(std::string position) { this->m_position = position; }

std::string Player::getSchool() const { return this->m_school; }

void Player::setSchool(std::string school) { this->m_school = school; }

int Player::getHeight() const { return this->m_height; }

void Player::setHeight(int height) { this->m_height; }

int Player::getWeight() const { return this->m_weight; }

void Player::setWeight(int weight) { this->m_weight; }

void Player::printInfo() const {
	printf("%d. %s || %s || %s || %d in. || %d lbs.\n", this->m_rank, this->m_name.c_str(), 
		this->m_position.c_str(), this->m_school.c_str(), this->m_height, this->m_weight);
}

void Player::printStats() const {
	std::cout << "Name: " << this->m_name << std::endl;
	std::cout << "School: " << this->m_school << std::endl;

	if (this->m_position == "QB" || this->m_position == "RB" || this->m_position == "WR" || this->m_position == "TE") {
		std::cout << "2022 College Statistics" << std::endl;
		std::cout << "-----------------------" << std::endl;
		if (this->m_offStats.has_value()) {
			(*m_offStats)->printStats();
		}
	}
	else if (this->m_position == "OT" || this->m_position == "iOL") {
		std::cout << "NO STATS AVAILABLE" << std::endl;
	}
	else if (this->m_position == "DL" || this->m_position == "EDGE" || this->m_position == "LB" ||
		this->m_position == "CB" || this->m_position == "S") {
		std::cout << "2022 College Statistics" << std::endl;
		std::cout << "-----------------------" << std::endl;
		if (this->m_defStats.has_value()) {
			(*m_defStats)->printStats();
		}
	}
}

void Player::clearData() {
	m_players.clear();
}

void Player::loadPlayers() {
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
			m_players.push_back(std::make_shared<Player>(rankCounter, name, position, school, newHeight, weight, offStats, defStats));
			rankCounter += 1;
		}

		FILE.close();
	}

}

int Player::heightParser(const std::string& height) {
	int feet, inches;
	std::istringstream strstm(height);
	char dash;
	strstm >> feet >> dash >> inches;
	return ((feet * 12) + inches);
}
