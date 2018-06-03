#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_status,
	OK,
	Wrong_length,
	Not_lowercase,
	Not_Isogram
};

class FBullCowGame {
public:
	//Public
	FBullCowGame(); //constructor
	void reset(); //TODO make return value
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 myCurrentTry;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuessValid(FString);
	//counting bulls & cows, and increasing try # 
	FBullCowCount SubmitValidGuess(FString);

private:
	//Private
	
	int32 myMaxTries;
	FString myHiddenWord;
	bool isIsogram(FString) const; //const because the function should not change anything (always case when using const)
	bool bGameIsWon;
	bool isLowercase(FString) const;
	bool isLower(char) const;
};
