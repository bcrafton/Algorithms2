// mastermind.cpp
// the mastermind class for the mastermind game
// Brian Crafton and Oliver Scott.

#include "mastermind.h"
#include <iostream>

using namespace std;

//default constructor
//  IN -- Nill
//  OUT -- Code Object

Mastermind::Mastermind()
{
}
//printSecretCode
//prints data member secretCode to the screne.
//  IN-- Nill
//  OUT-- Nill

void Mastermind::printSecretCode() const
{
	cout << "The secret code is: ";
	this->secretCode.printCode();
	cout << endl;
}
//getResponse
//compares two CODE objects and generates a RESPONSE object illustrating the proximity of the two CODES. assumes
//that the second CODE input is the object to be matched.
//  IN-- (CODE, CODE)
//  OUT-- RESPONSE
Response Mastermind::getResponse(const Code &guess, const Code &secretCode) const
{
	return Response(secretCode.checkCorrect(guess), secretCode.checkIncorrect(guess));
}
//playGame
//initializes a random code, prints it to the screen, and then iteratively gets a guess from the user and
//prints the response until either the codemaker or the codebreaker has won.
//  IN-- Nill
//  OUT-- Nill
void Mastermind::playGame()
{
	this->secretCode.generateCode();
	this->printSecretCode();

	int guessCount = 0;
	while(guessCount < 10)
	{
		Code guess = this->humanGuess();
		Response r = this->getResponse(guess, secretCode);
		if(this->isSolved(r))
		{
			cout << "Game is over, you win" << endl;
			break;
		}
		else
		{
			r.printResponse();
		}
		guessCount++;
		cout << "Guess Count: " << guessCount << endl;
	}
	if(guessCount >= 10)
	{
		cout << "Game is over, you lose" << endl;
	}
}
//humanGuess
//reads a single four digit input of integers as a guess, and returns the CODE object that
//represents this guess.
//  IN-- Nill
//  OUT-- CODE
Code Mastermind::humanGuess() const{
    Code guessCode;
    bool error;
    int guessInt;
    vector<int> guessVector(4);

    const int loopSize = guessVector.size();
    do{
        error = 0;
        for(int i = 0; i < loopSize; i++){
            cout << "\nEnter digit number " << (i + 1) << ": ";
            if(cin>>guessInt){
                if( ( guessInt < 0) || (guessInt > 6) ){
                    cout << "\nERROR: Input was not in range [0,5]." << endl;
                    error = 1;
                    break;
                }
                guessVector[i] = guessInt;
            }
            else{
                cin.clear();
                cin.ignore(256,'\n');
                cout << "\nERROR: Input not a valid integer." << endl;
                error = 1;
                break;
            }
        }
    }while(error);

    guessCode.setStoredCode(guessVector);

    cout << "\nThank You, your guess was: ";
    guessCode.printCode();
    cout << endl;
    return guessCode;
}
//isSolved
//checks to see if the game is solved
//  IN-- Response object
//  OUT-- boolean
bool Mastermind::isSolved(const Response r) const
{
	return r.getNumberCorrect() == 4;
}
