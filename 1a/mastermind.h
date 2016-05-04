// mastermind.h
// the header file for mastermind.cpp
// Brian Crafton and Oliver Scott.

#ifndef MASTERMIND_H
#define MASTERMIND_H
#include "code.h"
#include "response.h"
#include <iostream>

using namespace std;

// MASTERMIND: generates a mastermind object used to store the state of the game and play the game.
class Mastermind
{
	private:
		Code secretCode;
	public:
		Mastermind();
		void printSecretCode() const;
		Code humanGuess() const;
		Response getResponse(const Code &guess, const Code &secretCode) const;
		void playGame();
		bool isSolved(const Response r) const;
};


#endif
