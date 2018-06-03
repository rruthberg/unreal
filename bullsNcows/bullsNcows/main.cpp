#include "stdafx.h"		
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Define generic types for cross-platform use
using FText = std::string;
using int32 = int; 

//using namespace std;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetGuess();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; //new game

//Main function
int main() {
	PrintIntro();
	do {
		PlayGame();
	} while (AskToPlayAgain());
	
	return 0;
}


//Functions
void PrintIntro() {
	//Game introduction
	std::cout << "Welcome to Bulls and Cows, the worlds most fun word game!\n";
	std::cout << "Can you guess what " << BCGame.getHiddenWordLength();
	std::cout << " letter isogram I am thinking of?" << std::endl;
	return;
}

FText GetGuess() {
	//Get a guess from the player
	FText Guess = "";
	
	std::getline(std::cin, Guess);
	return Guess;
}

void PlayGame()
{
	BCGame.reset(); 
	int32 MaxTries = BCGame.getMaxTries();
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= MaxTries) {		
		FText Guess = GetValidGuess(); //TODO check valid guesses
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
	}
}


FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_status;
	FText Guess = "";
	do{
		int32 CurrTry = BCGame.getCurrentTry();
		std::cout << "Try " << CurrTry << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);
		Status = BCGame.checkGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << "letter word\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_lowercase:
			std::cout << "Please enter all lowercase letters.";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;

}


bool AskToPlayAgain()
{
	PrintGameSummary();
	std::cout << "Play again? (y/n)";
	FText response = "";
	std::getline(std::cin, response);
	return (response[0] == 'y') || (response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.isGameWon())
	{
		std::cout << "GAME WON. \n AWESOME U R HERO!! GONGRATS <3 HUGZ N KISSES" << std::endl;
	}
	else
	{
		std::cout << "GAME OVER. \n PLZ TRY AGAIN LOSER! LOLZ" << std::endl;
	}
	return;
}