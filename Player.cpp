#include <iostream>
#include <string>
#include <optional>
#include <cstdio>

#include "Player.h"

Player::Player() {}

// Add stats once constructors for Stats class are outlined
Player::Player(int rank, std::string name, std::string position,
	std::string school, int height, int weight, 
	std::optional<OffensiveStats*> offStats = std::nullopt,
	std::optional<DefensiveStats*> defStats = std::nullopt) : 
	m_rank(rank), 
	m_name(name),
	m_position(position),
	m_school(school),
	m_height(height),
	m_weight(weight),
	m_offStats(offStats),
	m_defStats(defStats) {}

int Player::getRank() { return this->m_rank; }

void Player::setRank(int rank) { this->m_rank = rank; }

std::string Player::getName() { return this->m_name; }

void Player::setName(std::string name) { this->m_name = name; }

std::string Player::getPosition() { return this->m_position; }

void Player::setPosition(std::string position) { this->m_position = position; }

std::string Player::getSchool() { return this->m_school; }

void Player::setSchool(std::string school) { this->m_school = school; }

int Player::getHeight() { return this->m_height; }

void Player::setHeight(int height) { this->m_height; }

int Player::getWeight() { return this->m_weight; }

void Player::setWeight(int weight) { this->m_weight; }

void Player::printInfo() {
	printf("%d. %s || %s || %s || %d in. || %d lbs.\n", this->m_rank, this->m_name.c_str(), 
		this->m_position.c_str(), this->m_school.c_str(), this->m_height, this->m_weight);
}

void Player::printStats() {
	std::cout << "Name: " << this->m_name << std::endl;
	std::cout << "School: " << this->m_school << std::endl;

	if (this->m_position == "QB" || this->m_position == "RB" || this->m_position == "WR" || this->m_position == "TE") {
		std::cout << "2022 College Statistics" << std::endl;
		std::cout << "-----------------------" << std::endl;
		if (this->m_offStats.has_value())
			(*m_offStats)->printStats();
	}
	else if (this->m_position == "OT" || this->m_position == "iOL") {
		std::cout << "NO STATS AVAILABLE" << std::endl;
	}
	else if (this->m_position == "DL" || this->m_position == "EDGE" || this->m_position == "LB" ||
		this->m_position == "CB" || this->m_position == "S") {
		std::cout << "2022 College Statistics" << std::endl;
		std::cout << "-----------------------" << std::endl;
		if (this->m_defStats.has_value())
			(*m_defStats)->printStats();
	}
}

void Player::clearData() {
	this->m_rank = 0;
	this->m_name.clear();
	this->m_position.clear();
	this->m_school.clear();
	this->m_height = 0;
	this->m_weight = 0;
	(*m_offStats)->clearData();
	(*m_defStats)->clearData();
}
