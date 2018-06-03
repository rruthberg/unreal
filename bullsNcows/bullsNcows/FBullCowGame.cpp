#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map //overwrite std::map with Tmap

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame()
{
	reset();
}

void FBullCowGame::reset()
{
	constexpr int32 MAX_TRIES = 5;
	myCurrentTry =  1;
	myMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = "planet";
	myHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::getMaxTries() const { return myMaxTries; }

int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }

int32 FBullCowGame::getHiddenWordLength() const{ return myHiddenWord.length(); }

bool FBullCowGame::isGameWon() const {return bGameIsWon;}

EGuessStatus FBullCowGame::checkGuessValid(FString Guess)
{
	if (!isIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowercase(Guess))
	{
		return EGuessStatus::Not_lowercase;
	}
	else if (Guess.length() != getHiddenWordLength() )
	{
		return EGuessStatus::Wrong_length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	//if no isogram, return enum
	//if no lowercase, return enum
	//if wrong lenght, return enum
	//else return OK
	//return EGuessStatus::OK; //TODO make actual error
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//Increment turn #
	//set a return variable
	//loop through letters in guess -> compare letters against hidden word in each 
	myCurrentTry++;
	FBullCowCount BC;
	int32 HiddenWordLength = getHiddenWordLength();
	for (int32 i = 0; i < HiddenWordLength; i++) 
	{
		for(int32 j = 0; j < HiddenWordLength; j++) 
		{
			if (Guess.at(i) == myHiddenWord.at(i) && i==j) 
			{
				BC.Bulls++;
			 }
			if (Guess.at(i) == myHiddenWord.at(j)) 
			{
				BC.Cows++;
			}
		}
	}
	if (BC.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BC;
}

bool FBullCowGame::isIsogram(FString Guess) const
{
	//treat 0 and 1 as isograms

	if (Guess.length() < 2) { return true; }

	TMap<char, bool> LetterSeen; 
	for (auto Letter : Guess) //for all letters in String, : defines the range-based for loop. Auto-keyword allows compiler to decide type
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::isLowercase(FString Word) const
{	
	for (auto Letter : Word)
	{
		if (!isLower(Letter)) { return false; }
	}
	return true;
}

bool FBullCowGame::isLower(char letter) const
{	
	if (!islower(letter)) { return false; }
	else { return true; }
}
