#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "PlayerBrowser.h"
#include "Stats.h"
#include "StatFileBuilder.h"

PlayerBrowser playerBrowser;
StatFileBuilder statFileBuilder;

void draft() {
	std::cout << "Draft" << std::endl;
}

void playerViewer() {
	int choice;
	bool runFlag = true;
	while (runFlag) {
		std::cout << "How would like to browse players?" << std::endl;
		std::cout << "\t1. Browse All" << std::endl;
		std::cout << "\t2. By Position" << std::endl;
		std::cout << "\t3. By School" << std::endl;
		std::cout << "\t4. Search for Specific Player" << std::endl;
		std::cout << "\t9. Back to Main Menu" << std::endl;
		std::cout << "\tSelect Option: ";

		if (std::cin >> choice) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			switch (choice) {
			case 1:
				playerBrowser.browseAll();
				break;
			case 2:
				playerBrowser.browseByPosition();
				break;
			case 3:
				playerBrowser.browseBySchool();
				break;
			case 4:
				playerBrowser.searchHandler();
				break;
			case 9:
				return;
			default:
				std::cout << "Please select a valid option" << std::endl;
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

void mainMenu() {
	int choice;
	bool runFlag = true;

	std::cout << "Welcome to the 2023 NFL Draft!" << std::endl;
	while (runFlag) {
		std::cout << "\n\tMAIN MENU" << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << "Please select what you wish to do" << std::endl;
		std::cout << "\t1. Begin Draft" << std::endl;
		std::cout << "\t2. Browse Players" << std::endl;
		std::cout << "\t3. Enter Player Statistics" << std::endl;
		std::cout << "\t9. Exit" << std::endl << std::endl;
		std::cout << "\tSelect Option: ";

		if (std::cin >> choice) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			switch (choice) {
			case 1:
				draft();
				break;
			case 2:
				playerViewer();
				break;
			case 3:
				statFileBuilder.confirmationMenu();
				break;
			case 9:
				std::cout << "Thanks for joining us. Exiting..." << std::endl;
				exit(-1);
			default:
				std::cout << "Please select a valid option" << std::endl;
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

int main() {
	mainMenu();
}
