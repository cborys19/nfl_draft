#include <iostream>
#include <string>

#include "Stats.h"

// Offensive stats
OffensiveStats::OffensiveStats(int rushYds, int rushTds, std::optional<int> passYds = std::nullopt,
	std::optional<int> passTds = std::nullopt, std::optional<int> ints = std::nullopt,
	std::optional<float> compPct = std::nullopt, std::optional<float> rating = std::nullopt,
	std::optional<int> receptions = std::nullopt, std::optional<int> recYds = std::nullopt,
	std::optional<int> recTds = std::nullopt,
	std::optional<float> avg = std::nullopt) : m_rushYds(rushYds), m_rushTds(rushTds),
	m_passYds(passYds), m_passTds(passTds),
	m_ints(ints), m_compPct(compPct),
	m_rating(rating), m_receptions(receptions),
	m_recYds(recYds), m_recTds(recTds),
	m_avg(avg) {}

int OffensiveStats::getRushingYards() { return this->m_rushYds; }

void OffensiveStats::setRushingYards(int rushYds) { this->m_rushYds = rushYds; }

int OffensiveStats::getRushingTouchdowns() { return this->m_rushTds; }

void OffensiveStats::setRushingTouchdowns(int rushTds) { this->m_rushTds = rushTds; }

std::optional<int> OffensiveStats::getPassingYards() { return this->m_passYds; }

void OffensiveStats::setPassingYards(std::optional<int> passYds) { this->m_passYds = passYds; }

std::optional<int> OffensiveStats::getInterceptions() { return this->m_ints; }

void OffensiveStats::setInterceptions(std::optional<int> ints) { this->m_ints = ints; }

std::optional<float> OffensiveStats::getCompletionPercentage() { return this->m_compPct; }

void OffensiveStats::setCompletionPercentage(std::optional<float> compPct) { this->m_compPct = compPct; }

std::optional<float> OffensiveStats::getQBRating() { return this->m_rating; }

void OffensiveStats::setQBRating(std::optional<float> rating) { this->m_rating = rating; }

std::optional<int> OffensiveStats::getReceivingYards() { return this->m_recYds; }

void OffensiveStats::setReceivingYards(std::optional<int> recYds) { this->m_recYds = recYds; }

std::optional<int> OffensiveStats::getReceivingTouchdowns() { return this->m_recTds; }

void OffensiveStats::setReceivingTouchdowns(std::optional<int> recTds) { this->m_recTds = recTds; }

std::optional<float> OffensiveStats::getAverageYardage() { return this->m_avg; }

void OffensiveStats::setAverageYardage(std::optional<float> avg) { this->m_avg = avg; }

void OffensiveStats::printStats() {
	if (m_passYds > 0 && m_passYds.has_value())
		std::cout << "Passing Yds: " << m_passYds.value() << std::endl;
	if (m_passTds > 0 && m_passTds.has_value())
		std::cout << "Passing TDs: " << m_passTds.value() << std::endl;
	if (m_rushYds > 0)
		std::cout << "Rushing Yds: " << m_rushYds << std::endl;
	if (m_rushTds > 0)
		std::cout << "Rushing TDs: " << m_rushTds << std::endl;
	if (m_ints > 0 && m_ints.has_value())
		std::cout << "Interceptions: " << m_ints.value() << std::endl;
	if (m_compPct > 0.0 && m_compPct.has_value())
		std::cout << "Completion Percentage: " << m_compPct.value() << std::endl;
	if (m_rating > 0.0 && m_rating.has_value())
		std::cout << "QB Rating: " << m_rating.value() << std::endl;
	if (m_recYds > 0 && m_recYds.has_value())
		std::cout << "Receiving Yds: " << m_recYds.value() << std::endl;
	if (m_recTds > 0 && m_recTds.has_value())
		std::cout << "Receiving TDs: " << m_recTds.value() << std::endl;
	if (m_avg > 0.0 && m_avg.has_value())
		std::cout << "Avg. Yardage: " << m_avg.value() << std::endl;
}

void OffensiveStats::clearData() {
	m_rushYds = 0;
	m_rushTds = 0;
	if (m_passYds.has_value())
		m_passYds.value() = 0;
	if (m_passTds.has_value())
		m_passTds.value() = 0;
	if (m_ints.has_value())
		m_ints.value() = 0;
	if (m_compPct.has_value())
		m_compPct.value() = 0;
	if (m_rating.has_value())
		m_rating.value() = 0;
	if (m_recYds.has_value())
		m_recYds.value() = 0;
	if (m_recTds.has_value())
		m_recTds.value() = 0;
	if (m_avg.has_value())
		m_avg.value() = 0;
}

// Defensive stats
DefensiveStats::DefensiveStats(int tackles, float sacks, int passDef, 
	int interceptions, int forcedFumbles) : m_tackles(tackles), m_sacks(sacks), m_passDef(passDef), 
	m_interceptions(interceptions), m_forcedFumbles(forcedFumbles) {};

int DefensiveStats::getTackles() { return this->m_tackles; }

void DefensiveStats::setTackles(int tackles) { this->m_tackles = tackles; }

float DefensiveStats::getSacks() { return this->m_sacks; }

void DefensiveStats::setSacks(float sacks) { this->m_sacks = sacks; }

int DefensiveStats::getPassesDefended() { return this->m_passDef; }

void DefensiveStats::setPassesDefended(int passDef) { this->m_passDef = passDef; }

int DefensiveStats::getInterceptions() { return this->m_interceptions; }

void DefensiveStats::setInterceptions(int interceptions) { this->m_interceptions = interceptions; }

int DefensiveStats::getForcedFumbles() { return this->m_forcedFumbles; }

void DefensiveStats::setForcedFumbles(int forcedFumbles) { this->m_forcedFumbles = forcedFumbles; }

void DefensiveStats::printStats() {
	std::cout << "Tackles: " << m_tackles << std::endl;
	std::cout << "Sacks: " << m_sacks << std::endl;
	std::cout << "Passes Defended: " << m_passDef << std::endl;
	std::cout << "Interceptions: " << m_interceptions << std::endl;
	std::cout << "Forced Fumbles: " << m_forcedFumbles << std::endl;
}

void DefensiveStats::clearData() {
	m_tackles = 0;
	m_sacks = 0;
	m_passDef = 0;
	m_interceptions = 0;
	m_forcedFumbles = 0;
}
