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

std::string Player::getSchool() { return m_school; }

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
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "School: " << m_school << std::endl;

	if (m_position == "QB" || m_position == "RB" || m_position == "WR" || m_position == "TE") {
		std::cout << "2022 College Statistics" << std::endl;
		std::cout << "-----------------------" << std::endl;
		if (m_offStats.has_value())
			(*m_offStats)->printStats();
	}
	else if (m_position == "OT" || m_position == "iOL") {
		std::cout << "NO STATS AVAILABLE" << std::endl;
	}
	else if (m_position == "DL" || m_position == "EDGE" || m_position == "LB" ||
			m_position == "CB" || m_position == "S") {
		std::cout << "2022 College Statistics" << std::endl;
		std::cout << "-----------------------" << std::endl;
		if (m_defStats.has_value())
			(*m_defStats)->printStats();
	}
}

void Player::clearData() {
	m_rank = 0;
	m_name.clear();
	m_position.clear();
	m_school.clear();
	m_height = 0;
	m_weight = 0;
	(*m_offStats)->clearData();
	(*m_defStats)->clearData();
}
