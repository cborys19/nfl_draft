#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <cstdio>

#include "Stats.h"

class Player {
private:
	int m_rank;

	std::string m_name;

	std::string m_position;

	std::string m_school;

	int m_height; // inches

	int m_weight; // pounds

	std::optional<OffensiveStats*> m_offStats;

	std::optional<DefensiveStats*> m_defStats;
public:
	Player();

	Player(int, std::string, std::string, std::string, int, int, std::optional<OffensiveStats*>, std::optional<DefensiveStats*>);

	int getRank();

	void setRank(int);
	
	std::string getName();

	void setName(std::string);

	std::string getPosition();

	void setPosition(std::string);

	std::string getSchool();

	void setSchool(std::string);

	int getHeight();

	void setHeight(int);

	int getWeight();

	void setWeight(int);

	void printInfo();

	void printStats();

	void clearData();
};