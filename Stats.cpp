#include <iostream>
#include <string>

#include "Stats.h"

// Offensive stats
//OffensiveStats::OffensiveStats(int rushYds, int rushTds, std::optional<int> passYds = std::nullopt,
//	std::optional<int> passTds = std::nullopt, std::optional<int> ints = std::nullopt,
//	std::optional<float> compPct = std::nullopt, std::optional<float> rating = std::nullopt,
//	std::optional<int> receptions = std::nullopt, std::optional<int> recYds = std::nullopt,
//	std::optional<int> recTds = std::nullopt,
//	std::optional<float> avg = std::nullopt) : m_rushYds(rushYds), m_rushTds(rushTds),
//	m_passYds(passYds), m_passTds(passTds),
//	m_ints(ints), m_compPct(compPct),
//	m_rating(rating), m_receptions(receptions),
//	m_recYds(recYds), m_recTds(recTds),
//	m_avg(avg) {}

int OffensiveStats::getRushingYards() const { return this->m_rushYds; }

void OffensiveStats::setRushingYards(int rushYds) { this->m_rushYds = rushYds; }

int OffensiveStats::getRushingTouchdowns() const { return this->m_rushTds; }

void OffensiveStats::setRushingTouchdowns(int rushTds) { this->m_rushTds = rushTds; }

std::optional<int> OffensiveStats::getPassingYards() const { return this->m_passYds; }

void OffensiveStats::setPassingYards(std::optional<int> passYds) { this->m_passYds = passYds; }

std::optional<int> OffensiveStats::getPassingTouchdowns() const { return this->m_passTds; }

void OffensiveStats::setPassingTouchdowns(std::optional<int> passTds) { this->m_passTds = passTds; }

std::optional<int> OffensiveStats::getPassingInterceptions() const { return this->m_ints; }

void OffensiveStats::setPassingInterceptions(std::optional<int> ints) { this->m_ints = ints; }

std::optional<float> OffensiveStats::getCompletionPercentage() const { return this->m_compPct; }

void OffensiveStats::setCompletionPercentage(std::optional<float> compPct) { this->m_compPct = compPct; }

std::optional<float> OffensiveStats::getQBRating() const { return this->m_rating; }

void OffensiveStats::setQBRating(std::optional<float> rating) { this->m_rating = rating; }

std::optional<int> OffensiveStats::getReceptions() const { return this->m_receptions; }

void OffensiveStats::setReceptions(std::optional<int> receptions) { this->m_receptions = receptions; }

std::optional<int> OffensiveStats::getReceivingYards() const { return this->m_recYds; }

void OffensiveStats::setReceivingYards(std::optional<int> recYds) { this->m_recYds = recYds; }

std::optional<int> OffensiveStats::getReceivingTouchdowns() const { return this->m_recTds; }

void OffensiveStats::setReceivingTouchdowns(std::optional<int> recTds) { this->m_recTds = recTds; }

std::optional<float> OffensiveStats::getAverageYardage() const { return this->m_avg; }

void OffensiveStats::setAverageYardage(std::optional<float> avg) { this->m_avg = avg; }

void OffensiveStats::printStats() const {
	if (this->m_passYds > 0 && this->m_passYds.has_value())
		std::cout << "Passing Yds: " << this->m_passYds.value() << std::endl;
	if (this->m_passTds > 0 && this->m_passTds.has_value())
		std::cout << "Passing TDs: " << this->m_passTds.value() << std::endl;
	if (this->m_rushYds > 0)
		std::cout << "Rushing Yds: " << this->m_rushYds << std::endl;
	if (this->m_rushTds > 0)
		std::cout << "Rushing TDs: " << this->m_rushTds << std::endl;
	if (this->m_ints > 0 && this->m_ints.has_value())
		std::cout << "Interceptions: " << this->m_ints.value() << std::endl;
	if (this->m_compPct > 0.0 && this->m_compPct.has_value())
		std::cout << "Completion Percentage: " << this->m_compPct.value() << std::endl;
	if (this->m_rating > 0.0 && this->m_rating.has_value())
		std::cout << "QB Rating: " << this->m_rating.value() << std::endl;
	if (this->m_recYds > 0 && this->m_recYds.has_value())
		std::cout << "Receiving Yds: " << this->m_recYds.value() << std::endl;
	if (this->m_recTds > 0 && this->m_recTds.has_value())
		std::cout << "Receiving TDs: " << this->m_recTds.value() << std::endl;
	if (this->m_avg > 0.0 && this->m_avg.has_value())
		std::cout << "Avg. Yardage: " << this->m_avg.value() << std::endl;
}

void OffensiveStats::clearData() {
	this->m_rushYds = 0;
	this->m_rushTds = 0;
	if (this->m_passYds.has_value())
		this->m_passYds.value() = 0;
	if (m_passTds.has_value())
		this->m_passTds.value() = 0;
	if (m_ints.has_value())
		this->m_ints.value() = 0;
	if (m_compPct.has_value())
		this->m_compPct.value() = 0;
	if (m_rating.has_value())
		this->m_rating.value() = 0;
	if (m_recYds.has_value())
		this->m_recYds.value() = 0;
	if (m_recTds.has_value())
		this->m_recTds.value() = 0;
	if (m_avg.has_value())
		this->m_avg.value() = 0;
}

// Defensive stats
DefensiveStats::DefensiveStats(int tackles, float sacks, int passDef, 
	int interceptions, int forcedFumbles) : m_tackles(tackles), m_sacks(sacks), m_passDef(passDef), 
	m_interceptions(interceptions), m_forcedFumbles(forcedFumbles) {};

int DefensiveStats::getTackles() const { return this->m_tackles; }

void DefensiveStats::setTackles(int tackles) { this->m_tackles = tackles; }

float DefensiveStats::getSacks() const { return this->m_sacks; }

void DefensiveStats::setSacks(float sacks) { this->m_sacks = sacks; }

int DefensiveStats::getPassesDefended() const { return this->m_passDef; }

void DefensiveStats::setPassesDefended(int passDef) { this->m_passDef = passDef; }

int DefensiveStats::getInterceptions() const { return this->m_interceptions; }

void DefensiveStats::setInterceptions(int interceptions) { this->m_interceptions = interceptions; }

int DefensiveStats::getForcedFumbles() const { return this->m_forcedFumbles; }

void DefensiveStats::setForcedFumbles(int forcedFumbles) { this->m_forcedFumbles = forcedFumbles; }

void DefensiveStats::printStats() const {
	std::cout << "Tackles: " << this->m_tackles << std::endl;
	std::cout << "Sacks: " << this->m_sacks << std::endl;
	std::cout << "Passes Defended: " << this->m_passDef << std::endl;
	std::cout << "Interceptions: " << this->m_interceptions << std::endl;
	std::cout << "Forced Fumbles: " << this->m_forcedFumbles << std::endl;
}

void DefensiveStats::clearData() {
	this->m_tackles = 0;
	this->m_sacks = 0;
	this->m_passDef = 0;
	this->m_interceptions = 0;
	this->m_forcedFumbles = 0;
}
