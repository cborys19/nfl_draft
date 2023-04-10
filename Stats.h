#pragma once

#include <iostream>
#include <string>
#include <optional>

// OffensiveStats class - derived from Stats
// Represents shared stats for Quarterbacks, Running Backs, Wide Receivers, and Tight Ends
class OffensiveStats {
protected:
	int m_rushYds; // Rushing yards (QB/RB/WR/TE)

	int m_rushTds; // Rushing touchdowns (QB/RB/WR/TE)

	std::optional<int> m_passYds; // Passing yards (QB)

	std::optional<int> m_passTds; // Passing touchdowns (QB)

	std::optional<int> m_ints; // Passing interceptions (QB)

	std::optional<float> m_compPct; // Completion percentage (QB)

	std::optional<float> m_rating; // Quarterback rating (QB)

	std::optional<int> m_receptions; // Receptions (RB/WR/TE)

	std::optional<int> m_recYds; // Receiving yards (RB/WR/TE)

	std::optional<int> m_recTds; // Receiving touchdowns (RB/WR/TE)

	std::optional<float> m_avg; // RBs = avg. yards/carry; WRs/TEs = avg. yards/reception
public:
	OffensiveStats() = default;

	OffensiveStats(int, int, std::optional<int>, std::optional<int>, std::optional<int>, 
		std::optional<float>, std::optional<float>, std::optional<int>, std::optional<int>, 
		std::optional<int>, std::optional<float>);

	int getRushingYards(); // Rushing yards getter

	void setRushingYards(int); // Rushing yards setter

	int getRushingTouchdowns(); // Rushing touchdown getter

	void setRushingTouchdowns(int); // Rushing touchdown setter

	std::optional<int> getPassingYards(); // Passing yard getter

	void setPassingYards(std::optional<int>); // Passing yard setter

	std::optional<int> getInterceptions(); // Interception getter

	void setInterceptions(std::optional<int>); // Interception setter

	std::optional<float> getCompletionPercentage(); // Completion percentage getter

	void setCompletionPercentage(std::optional<float>); // Completion percentage setter

	std::optional<float> getQBRating(); // QB rating getter

	void setQBRating(std::optional<float>); // QB rating setter

	std::optional<int> getReceivingYards(); // Receiving yard getter

	void setReceivingYards(std::optional<int>); // Receiving yard setter

	std::optional<int> getReceivingTouchdowns(); // Receiving touchdown getter

	void setReceivingTouchdowns(std::optional<int>); // Receiving touchdown setter

	std::optional<float> getAverageYardage(); // Average yardage getter

	void setAverageYardage(std::optional<float>); // Average yardage setter

	void printStats(); // Print stats associated with given player

	void clearData();
};

class DefensiveStats{
protected:
	int m_tackles; // Number of tackles
	
	float m_sacks; // Number of sacks
	
	int m_passDef; // Number of passes defended
	
	int m_interceptions; // Number of interceptions
	
	int m_forcedFumbles; // Number of forced fumbles
public:
	DefensiveStats() = default;

	DefensiveStats(int, float, int, int, int);

	int getTackles(); // Tackles getter
	
	void setTackles(int); // Tackles setter
	
	float getSacks(); // Sack getter
	
	void setSacks(float); // Sack setter
	
	int getPassesDefended(); // Passes defended getter
	
	void setPassesDefended(int); // Passes defended setter
	
	int getInterceptions(); // Interception getter
	
	void setInterceptions(int); // Interception setter
	
	int getForcedFumbles(); // Forced fumble getter
	
	void setForcedFumbles(int); // Forced fumble setter
	
	void printStats(); // Print states associated with a given player

	void clearData();
};