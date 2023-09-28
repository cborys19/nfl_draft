#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <optional>
#include <cstdio>
#include <memory>
#include <vector>

#include "Stats.h"

class Player {
private:
	void loadPlayers();

	int heightParser(const std::string&);

	std::vector<std::shared_ptr<Player>> m_players;

	int m_rank;

	std::string m_name;

	std::string m_position;

	std::string m_school;

	int m_height; // inches

	int m_weight; // pounds

	std::optional<std::shared_ptr<OffensiveStats>> m_offStats;

	std::optional<std::shared_ptr<DefensiveStats>> m_defStats;
public:
	Player();

	Player(int, std::string, std::string, std::string, int, int, std::optional<std::shared_ptr<OffensiveStats>>, std::optional<std::shared_ptr<DefensiveStats>>);

	int getRank() const;

	void setRank(int);
	
	std::string getName() const;

	void setName(std::string);

	std::string getPosition() const;

	void setPosition(std::string);

	std::string getSchool() const;

	void setSchool(std::string);

	int getHeight() const;

	void setHeight(int);

	int getWeight() const;

	void setWeight(int);

	void printInfo() const;

	void printStats() const;

	void clearData();

	friend class PlayerBrowser;

	friend class StatFileBuilder;
};