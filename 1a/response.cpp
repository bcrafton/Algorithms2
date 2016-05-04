// response.cpp
// the response class for the mastermind game
// Brian Crafton and Oliver Scott.
#include "response.h"
#include <iostream>

using namespace std;
/*CONSTRUCTORS*/
//Default
//defaults to no digits accounted for.
Response::Response()
{
	this->numberCorrect = 0;
	this->numberIncorrect = 0;
}
//Provided
//creates a new response with the two integer values provided.
//   IN-- Int, Int
//   OUT-- RESPONSE
Response::Response(int numberCorrect, int numberIncorrect)
{
	this->numberCorrect = numberCorrect;
	this->numberIncorrect = numberIncorrect;
}
/*GETTERS*/

int Response::getNumberCorrect() const
{
	return this->numberCorrect;
}
//getIncorrect

int Response::getNumberIncorrect() const
{
	return this->numberIncorrect;
}
/*SETTERS*/

void Response::setNumberCorrect(int numberCorrect)
{
	this->numberCorrect = numberCorrect;
}
//setIncorrect

void Response::setNumberIncorrect(int numberIncorrect)
{
	this->numberIncorrect = numberIncorrect;
}

//printResponse
//prints the RESPONSE data member values
//  IN-- Nill
//  OUT-- Nill
void Response::printResponse() const
{
	cout << "Number of correct: " << this->numberCorrect << endl << "Number of incorrect: " << this->numberIncorrect << endl;
}



