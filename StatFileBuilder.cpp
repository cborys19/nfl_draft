#include "StatFileBuilder.h"

//StatFileBuilder::StatFileBuilder() {
//	this->FILE.open("stats.txt", std::fstream::app);
//}

//void StatFileBuilder::closeFile() {
//	this->FILE.close();
//}

void StatFileBuilder::confirmationMenu() {
	int choice;
	bool runFlag = true;
	std::cout << "Are you sure you want to edit statistical information?" << std::endl;
	std::cout << "This may completely overwrite all data, causing undefined behavior" << std::endl;
	while (runFlag) {
		std::cout << "Enter 1 to confirm, 2 to go back to safety: ";

		if (std::cin >> choice) {
			switch (choice) {
			case 1:
				fileBuilder();
				runFlag = false;
				break;
			case 2:
				return;
			default:
				std::cout << "Error: Please enter either 1 or 2" << std::endl;
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

StatFileBuilder::Position StatFileBuilder::convertStrToPos(const std::string& pos) {
	if (pos == "QB") {
		return QUARTERBACK;
	}
	else if (pos == "RB" || pos == "WR" || pos == "TE") {
		return SKILL;
	}
	else if (pos == "OT" || pos == "iOL") {
		return OFFENSIVELINEMAN;
	}
	else if (pos == "EDGE" || pos == "DL" || pos == "CB" || pos == "S" || pos == "LB") {
		return DEFENSE;
	}
	else {
		return INVALID;
	}
}

void StatFileBuilder::fileBuilder() {
	std::fstream FILE("stats.txt");
	if (!FILE.is_open()) {
		std::cout << "stats.txt COULD NOT BE FOUND" << std::endl;
		std::cout << "Sorry!" << std::endl;
		return;
	}

	std::shared_ptr<OffensiveStats> offStatsPtr = nullptr;
	std::shared_ptr<DefensiveStats> defStatsPtr = nullptr;

	std::string line, pos;
	for (int i = 0; i < playerObj.m_players.size(); i++) {
		while (std::getline(FILE, line)) {
			if (playerObj.m_players[i]->getName() == line) {
				pos = playerObj.m_players[i]->getPosition();
				switch (convertStrToPos(pos)) {
				case QUARTERBACK:
					offStatsPtr = buildQB(playerObj.m_players[i]->getName());
					break;
				case SKILL:
					offStatsPtr = buildSkill(playerObj.m_players[i]->getName());
					break;
				case OFFENSIVELINEMAN:
					offStatsPtr = buildOL(playerObj.m_players[i]->getName());
					break;
				case DEFENSE:
					defStatsPtr = buildDef(playerObj.m_players[i]->getName());
					break;
				case INVALID:
					std::cout << "Error: Expected value, please inspect players.txt" << std::endl;
					return;
				}

				// TODO
				// -----------------------
				// create setter for offensive/defensive stats
				// set returned stats pointer to player in switch statement
				// print values in stats pointer to file
			}
		}
	}
	FILE.close();
}

std::shared_ptr<OffensiveStats> StatFileBuilder::buildQB(const std::string& name) {
	std::shared_ptr<OffensiveStats> stats = std::make_shared<OffensiveStats>();
	int rushYds, rushTds, passYds, passTds, ints;
	float compPct, rating;
	auto inputValidation = [](const std::string& prompt, auto& stat) {
		while (true) {
			std::cout << prompt;
			if (std::cin >> stat) {
				break;
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << std::endl;
				std::cout << "Error: Please enter valid value" << std::endl;
			}
		}
	};

	std::cout << "Enter the following stats for " << name << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	inputValidation("Rushing Yards: ", rushYds);
	stats->setRushingYards(rushYds);
	inputValidation("Rushing Touchdowns: ", rushTds);
	stats->setRushingTouchdowns(rushTds);
	inputValidation("Passing Yards: ", passYds);
	stats->setPassingYards(passYds);
	inputValidation("Passing Touchdowns: ", passTds);
	stats->setPassingTouchdowns(passTds);
	inputValidation("Interceptions: ", ints);
	stats->setPassingInterceptions(ints);
	inputValidation("Completion Percentage (round to one decimal): ", compPct);
	stats->setCompletionPercentage(compPct);
	inputValidation("QB Rating (round to one decimal): ", rating);
	stats->setQBRating(rating);

	return stats;
}

std::shared_ptr<OffensiveStats> StatFileBuilder::buildSkill(const std::string& name) {
	std::shared_ptr<OffensiveStats> stats = std::make_shared<OffensiveStats>();
	int rushYds, rushTds, receptions, recYds, recTds;
	float avg;
	auto inputValidation = [](const std::string& prompt, auto& stat) {
		while (true) {
			std::cout << prompt;
			if (std::cin >> stat) {
				break;
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << std::endl;
				std::cout << "Error: Please enter valid value" << std::endl;
			}
		}
	};

	std::cout << "Enter the following stats for " << name << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	inputValidation("Rushing Yards: ", rushYds);
	stats->setRushingYards(rushYds);
	inputValidation("Rushing Touchdowns: ", rushTds);
	stats->setRushingTouchdowns(rushTds);
	inputValidation("Receptions: ", receptions);
	stats->setReceptions(receptions);
	inputValidation("Receiving Yards: ", recYds);
	stats->setReceivingYards(recYds);
	inputValidation("Receiving Touchdowns: ", recTds);
	stats->setReceivingYards(recTds);
	inputValidation("Avg. Yards/Reception (round to one decimal): ", avg);
	stats->setAverageYardage(avg);

	return stats;
}

std::shared_ptr<OffensiveStats> StatFileBuilder::buildOL(const std::string& name) {
	std::shared_ptr<OffensiveStats> stats = std::make_shared<OffensiveStats>();
	return stats;
}

std::shared_ptr<DefensiveStats> StatFileBuilder::buildDef(const std::string& name) {
	std::shared_ptr<DefensiveStats> stats = std::make_shared<DefensiveStats>();
	int tackles, passDef, ints, forcedFumbles;
	float sacks;
	auto inputValidation = [](const std::string& prompt, auto& stat) {
		while (true) {
			std::cout << prompt;
			if (std::cin >> stat) {
				break;
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << std::endl;
				std::cout << "Error: Please enter valid value" << std::endl;
			}
		}
	};

	std::cout << "Enter the following stats for " << name << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	inputValidation("Tackles: ", tackles);
	stats->setTackles(tackles);
	inputValidation("Sacks: ", sacks);
	stats->setSacks(sacks);
	inputValidation("Passes Defended: ", passDef);
	stats->setPassesDefended(passDef);
	inputValidation("Interceptions: ", ints);
	stats->setInterceptions(ints);
	inputValidation("Forced Fumbles: ", forcedFumbles);
	stats->setForcedFumbles(forcedFumbles);

	return stats;
}
