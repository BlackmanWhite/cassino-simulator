#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// User
string playerName;
unsigned int money = 100;

// Bank
unsigned int bankBalance = 10;
int bankDebt;
short int bankInterest;

// Betting
unsigned int bet;

// Guessing game
short unsigned int guess;
short unsigned int dice;
unsigned int moneyBet;

// --- Blackjack ---
short unsigned int cardNum;
bool gameOver = false;
bool firstTurn = true;
// Player
short unsigned int pTotal;
bool pStand = false;
// CPU
short unsigned int cpuTotal;
short unsigned int cpuChoice;
bool cpuStand = false;
short unsigned int cpuDifficulty = 2; // 1 = Safe, 2 = Normal, 3 = Risky

// App
const string help = "\n=============== Commands ===============\n[1] Cassino\n[2] Bank\n[3] Help\n[4] Options\n[5] Exit\n\n";
short unsigned int prompt;
bool execMenu = false;
bool isRunning;

int getBet() {
	bet = 0;
	std::cout << "\nHow much do you wish to bet (1 - " << money << "): ";
	std::cin >> moneyBet;
	if (moneyBet > money) {
		std::cout << "\nYou don't have " << moneyBet << "$ to bet...\n";
		return execMenu = true;
	}
	else if (moneyBet < 1) {
		std::cout << "\nYou need to bet more than 1$\n";
		return execMenu = true;
	}
	return bet;
}

int input() {
	std::cout << "> ";
	std::cin >> prompt;
	return prompt;
}

bool options() {
	std::cout << "===== Options =====\n[1] Name: " << playerName << endl << "[2] CPU difficulty: " << cpuDifficulty << endl << "[3] Return\n\n";
	input();
	if (prompt == 1) {
		std::cout << "\nName: ";
		cin >> playerName;
		std::cout << endl;
		options();
	}
	else if (prompt == 2) {
		std::cout << "\nCPU difficulty: ";
		cin >> cpuDifficulty;
		std::cout << endl;
		options();
	}
	else if (prompt == 3) {
		return execMenu = true;
	}
}

bool gamble() {
	getBet();
	std::cout << "\nChoose a number (0-9): ";
	std::cin >> bet;

	dice = rand() % 8 + 1;
	std::cout << "\nNumber rolled was " << dice << endl;
	if (bet == dice) {
		std::cout << "You lost the bet\n";
		std::cout << "You betted " << moneyBet << "$\n";
		std::cout << money << "$ + " << moneyBet << "$ = ";
		money -= moneyBet;
		std::cout << money << "$" << endl;
	}
	else if (bet != dice) {
		std::cout << "You lost the bet\n";
		std::cout << "You betted " << moneyBet << "$\n";
		std::cout << money << "$ - " << moneyBet << "$ = ";
		money -= moneyBet;
		std::cout << money << "$" << endl;
	}
	else {
		std::cout << "[UKNOWN ERROR]\n\n-----[ DEBUG ]-----\n" << "Bet = " << bet << endl << "Dice = " << dice;
	}
	std::cout << "Now you have " << money << "$\n";
	return execMenu = true;
}

void blackjackCPU(int _cpuTotal, int _playerTotal) {
	if (cpuDifficulty = 2) {
		// Normal
		if (_cpuTotal == cpuTotal <= 13 || _cpuTotal < _playerTotal) {
			// Hit
			cpuChoice = 1;
		}
		else if (_cpuTotal > 13 && _cpuTotal > _playerTotal) {
			// Stand
			cpuChoice = 2;
		}
	}
	else if (cpuDifficulty = 1) {
		// Safe
		if (_cpuTotal == cpuTotal <= 8 || _cpuTotal < _playerTotal) {
			// Hit
			cpuChoice = 1;
		}
		else if (_cpuTotal > 8 && _cpuTotal > _playerTotal) {
			// Stand
			cpuChoice = 2;
		}
	}
	else if (cpuDifficulty = 3) {
		// Risky
		if (_cpuTotal == cpuTotal <= 17 || _cpuTotal < _playerTotal) {
			// Hit
			cpuChoice = 1;
		}
		else if (_cpuTotal > 17 && _cpuTotal > _playerTotal) {
			// Stand
			cpuChoice = 2;
		}
	}
}

bool blackjack() {
	gameOver = false;
	firstTurn = true;
	// Player
	pTotal = 0;
	pStand = false;
	// CPU
	cpuTotal = 0;
	cpuStand = false;
	getBet();
	while (gameOver == false) {

		if (pStand == false) {
			if (firstTurn == false) {
				std::cout << "\nPlayer chooses to hit";
			}
			cardNum = rand() % 13;
			std::cout << "\nPlayer pulled out a " << cardNum << endl;
			pTotal += cardNum;
			std::cout << "Player total: " << pTotal << endl;
		}
		else {
			std::cout << "\nPlayer chooses to stand\n";
		}
		if (cpuStand == false) {
			if (firstTurn == false) {
				std::cout << "\nCPU chooses to hit";
			}
			cardNum = rand() % 13;
			std::cout << "\nCPU pulled out a " << cardNum << endl;
			cpuTotal += cardNum;
			std::cout << "CPU total: " << cpuTotal << endl;
		}
		else {
			std::cout << "\nCPU chooses to stand\n";
		}
		firstTurn = false;
		if (pTotal > 21 && cpuTotal <= 21 || pStand == true && cpuStand == true && cpuTotal - 21 > pTotal - 21) {
			// CPU
			std::cout << "\n--- CPU WON ---\nPlayer total: " << pTotal << "\nCPU total: " << cpuTotal << endl << endl;
			money -= moneyBet;
			std::cout << "You lost " << moneyBet << "$\nNow you have " << money << "$\n";
			gameOver = true;
		}
		else if (cpuTotal > 21 && pTotal <= 21 || pStand == true && cpuStand == true && cpuTotal - 21 < pTotal - 21) {
			// Player
			std::cout << "\n--- PLAYER WON ---\nPlayer total: " << pTotal << "\nCPU total: " << cpuTotal << endl << endl;
			money += moneyBet;
			std::cout << "You won " << moneyBet << "$\nNow you have " << money << "$\n";
			gameOver = true;
		}
		else if (cpuTotal > 21 && pTotal > 21 || pStand == true && cpuStand == true && cpuTotal - 21 == pTotal - 21) {
			// Draw
			std::cout << "\n--- DRAW ---\nPlayer total: " << pTotal << "\nCPU total: " << cpuTotal << endl << endl;
			gameOver = true;
			return execMenu = true;
		}
		blackjackCPU(cpuTotal, pTotal);
		if (cpuStand == false && cpuChoice == 2) {
			cpuStand = true;
		}
		if (pStand == false) {
			std::cout << "\n[1] Hit | [2] Stand\n\n";
			input();
			if (prompt == 1) {
				// Hit
				gameOver = false;
			}
			else if (prompt == 2) {
				// Stand
				pStand = true;
			}
		}
	}
	return execMenu = true;
}

bool bank() {
	std::cout << "\n===== " << playerName << "'s bank account =====\nBalance: " << bankBalance << "\nDebts: " << bankDebt << "\nMoney in-hand: " << money;
	std::cout << "\n\n[1] Deposit\n[2] Withdraw\n[3] Loans\n[4] Return\n\n";
	input();
	if (prompt == 1) {
		// Deposit
		std::cout << "\nHow much do you wish to deposit? (1 - " << money << ")\n";
		input();
		if (prompt > money) {
			std::cout << "\nYou don't have enough money in hand, try again\n";
			return execMenu = true;
		}
		else {
			money -= prompt;
			bankBalance += prompt;
			std::cout << "\nYou sucessfully deposited " << prompt << "$\n";
			return execMenu = true;
		}
	}
	else if (prompt == 2) {
		// Withdraw
		std::cout << "\nHow much do you wish to withdraw? (1 - " << bankBalance << ")\n";
		input();
		if (prompt > bankBalance) {
			std::cout << "\nYou don't have enough money in the bank, try again\n";
			return execMenu = true;
		}
		else {
			money += prompt;
			bankBalance -= prompt;
			std::cout << "\nYou sucessfully withdrawed " << prompt << "$\n";
			return execMenu = true;
		}
	}
	else if (prompt == 3) {
		// Loans
		return execMenu = true;
	}
	else if (prompt == 4) {
		// Return
		return execMenu = true;
	}
	else {
		// Invalid command
		std::cout << "\nInvalid command\n";
		return execMenu = true;
	}
}

bool cassino() {
	std::cout << "\n===== Virtual cassino =====\n";
	std::cout << "[1] Gamble\n[2] Blackjack\n[3] Return\n\n";

	input();

	if (prompt == 1) {
		// Number roll
		gamble();
	}
	else if (prompt == 2) {
		// Blackjack
		blackjack();
	}
	else if (prompt == 3) {
		// Return
		return execMenu = true;
	}
	else {
		// Invalid command
		std::cout << "\nInvalid command\n";
		return execMenu = true;
	}
}

int menu() {
	std::cout << help;
	input();

	if (prompt == 1) {
		// Cassino
		cassino();
	}
	else if (prompt == 2) {
		// Bank
		bank();
	}
	else if (prompt == 3) {
		// Help
		menu();
	}
	else if (prompt == 4) {
		// Options
		options();
	}
	else if (prompt == 5) {
		// Exit
		std::cout << "\n\nExiting program...\n\n";
		return 0;
	}
	else {
		// Invalid command
		std::cout << "\nInvalid command\n";
		menu();
	}
}

int main()
{
	srand(time(NULL));
	isRunning = true;
	std::cout << "Enter your name: ";
	std::cin >> playerName;

	std::cout << "\nHello " << playerName << "!\nWelcome to the virtual cassino\nHere you can bet in various games\nI gave you 100$ so you can start with something, don't waste all in one bet\nIn the bank you can deposit some extra cash to make profit over time\nAlso, loans are avaliable in the banks if you need some money\nNow go out there and make some profit!\n\n";
	menu();
	while (isRunning == true) {
		if (execMenu == true) {
			execMenu = false;
			menu();
		}
		else {
			std::cout << "\nClose game received...\n";
			return 0;
		}
	}
}

