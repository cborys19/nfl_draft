#pragma once

#include <iostream>
#include <fstream>
#include <memory>

#include "Player.h"
#include "Stats.h"

class StatFileBuilder {
private:
	Player playerObj;

	enum Position {
		QUARTERBACK,
		SKILL,
		OFFENSIVELINEMAN,
		DEFENSE,
		INVALID
	};

	~StatFileBuilder() = default;

	Position convertStrToPos(const std::string&);

	//std::fstream FILE;

	//void closeFile();

	void fileBuilder();

	std::shared_ptr<OffensiveStats> buildQB(const std::string&);

	std::shared_ptr<OffensiveStats> buildSkill(const std::string&);

	std::shared_ptr<OffensiveStats> buildOL(const std::string&);

	std::shared_ptr<DefensiveStats> buildDef(const std::string&);

public:
	//StatFileBuilder();

	StatFileBuilder() = default;

	void confirmationMenu();
};
