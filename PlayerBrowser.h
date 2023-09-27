#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "Player.h"

// class for handling browsing players
// will contain various methods for browsing player information
// eventually add methods for messing with stats

class PlayerBrowser {
private:
	Player playerObj;

	void sortPrompt(); // will ask the user what to sort by

	//void sortBySchool();
	
	//void sortByHeight();

	//void sortByWeight();

	//void sortByPosition();

	//void search(std::string&);

public:
	PlayerBrowser() = default;

	void browseAll();

	void browseByPosition();

	void browseBySchool();

	//friend class Player; // load players from file Player class; this class can then use those Players
};
