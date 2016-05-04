// mastermind.h
// the header file for mastermind.cpp
// Brian Crafton and Oliver Scott.

#ifndef MASTERMIND_H
#define MASTERMIND_H
#include "code.h"
#include "d_except.h"
//#include "response.h"
#include <iostream>

using namespace std;

//Universe of all previously made guesses and associated responses
struct PastGuess{
    Code guess;
    Response response;
};

// MASTERMIND: generates a mastermind object used to store the state of the game and play the game.
class Mastermind
{
private:
    Code secretCode;
    vector<PastGuess> pastGuesses;
public:
    //Setters,Getters,Constructors
    Mastermind();
    void newPastGuess(const Code &newGuess, const Response &newResponse) throw(baseException);
    
    
    //Functions
    void printSecretCode() const;
    Response getResponse(const Code &guess, const Code &secretCode) const;
    Code humanGuess() const;
    void playGame();
    void playGame2() throw(baseException);
    bool isSolved(const Response r) const throw(baseException);
    bool consistentWithGuess(const Code &pastGuess, const Response &pastResponse, const Code &guess)const throw(baseException);
    bool consistentWithPreviousGuesses(Code const &guess)const throw(baseException);
    Code agentGuess()const;
	int calculateScore(const Code candidateCode)const throw(baseException);
    friend ostream &operator <<(ostream &ostr, const Mastermind &game);
    
};



#endif
