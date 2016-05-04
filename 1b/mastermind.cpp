// mastermind.cpp
// the mastermind class for the mastermind game
// Brian Crafton and Oliver Scott.

#include "mastermind.h"
#include <iostream>

using namespace std;

//* * * * * * * * * * * * * * * * * * * *
// * * * SETTERS,GETTERS,CONSTRUCTORS * *
//* * * * * * * * * * * * * * * * * * * *

//default constructor
Mastermind::Mastermind()
{
}

//newPastGuess
//adds another guess and response to list of previous guesses.
//  IN-- (Code, Response)
//  OUT-- boolean
void Mastermind::newPastGuess(const Code &newGuess, const Response &newResponse) throw (baseException){ 
	if(newGuess.getCode().size() != 4)
	{
		throw "vector size not equal to 4";
	}
	if(newResponse.getNumberCorrect() < 0 || newResponse.getNumberIncorrect() < 0)
	{
		throw "number correct less than 0";
	}
    const PastGuess thisGuess = {newGuess, newResponse};
    pastGuesses.push_back(thisGuess);
}

//* * * * * * * * * * * * * * *
//* * * F U N C T I O N S * * *
//* * * * * * * * * * * * * * *

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

//playGame2
//takes an input from the user and sets it to the secretCode data member, prints it to the screen, and then the computer
//iteravely attempts to determine the value of the guess.
//  IN-- Nill
//  OUT-- Nill
void Mastermind::playGame2() throw (baseException)
{
    Code userCode;
    bool error;
    int guessInt;
    vector<int> userVector(4);
    pastGuesses.clear();
    
    const int loopSize = userVector.size();
    do{
        error = 0;
        for(int i = 0; i < loopSize; i++){
            cout << "\nEnter digit number " << (i + 1) << ": ";
            if(cin>>guessInt){
                if( ( guessInt < 0) || (guessInt > 5) ){
                    throw "\nERROR: Input was not in range [0,5].";
                    error = 1;
                    break;
                }
                userVector[i] = guessInt;
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
    
    secretCode.setStoredCode(userVector);
    cout << "\nThank You, the secret code has been set as: " << *this << endl;
    PastGuess newGuess;
    
    bool gameOver;
    int guessCounter = 0;
    do{
        const Code computerGuess = agentGuess();
        const Response r = getResponse(computerGuess, secretCode);
        guessCounter++;
        cout << "\nGuess Count: " << guessCounter << "\nComputer Guess: " << computerGuess << "\nResponse: " << r << endl;
        newGuess.guess = computerGuess;
        newGuess.response = r;
        pastGuesses.push_back(newGuess);
        gameOver = this->isSolved(r);
    }while(!gameOver);
}

//humanGuess
//reads a single four digit input of integers as a guess, and returns the CODE object that
//represents this guess.
//  IN-- Nill
//  OUT-- CODE
Code Mastermind::humanGuess() const
{
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
                if( ( guessInt < 0) || (guessInt > 5) ){
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
//  IN-- RESPONSE
//  OUT-- Boolean
bool Mastermind::isSolved(const Response r) const throw (baseException)
{
	if(r.getNumberCorrect() < 0 && r.getNumberIncorrect() < 0)
	{
		throw("Invalid response object");
	}
    bool solved = r.getNumberCorrect() == 4;
	if (solved)
    {
        cout << "\n * * * * * * * * * * * * * * * * * * * *" << "\n GAME OVER: Computers are our overlords." << "\n * * * * * * * * * * * * * * * * * * * *" << endl;
    }
    return solved;
}

//consistentWithPreviousGuess
//determines if one guess is consistent with a previous guess dependent upon the result of the previous guess. returns
//the assessment of consisitency
//  IN-- (CODE, RESPONSE, CODE)
//  OUT-- Boolean
bool Mastermind::consistentWithGuess(Code const &pastGuess, Response const &pastResponse, Code const &guess)const throw (baseException)
{
	if(pastResponse.getNumberCorrect() < 0 && pastResponse.getNumberIncorrect() < 0)
	{
		throw("Invalid response object");
	}
	if(pastGuess.getCode().size() != 4)
	{
		throw "vector size not equal to 4";
	}
	if(guess.getCode().size() != 4)
	{
		throw "vector size not equal to 4";
	}

    bool consistent = 0;
    const int correct = pastGuess.checkCorrect(guess);
    const int incorrect = pastGuess.checkIncorrect(guess);
    Response newResponse(correct, incorrect);
    if(newResponse == pastResponse) consistent = 1;
    return consistent;
}

//consistentWithPreviousGuesses
//decides whether or not a guess is consistent with the data structure of pastGuesses (vector<PastGuess>).
//  IN-- CODE
//  OUT-- Boolean
bool Mastermind::consistentWithPreviousGuesses(Code const &guess)const throw (baseException)
{
	if(guess.getCode().size() != 4)
	{
		throw "vecotr size greater than 4";
	}
    const int loopSize = pastGuesses.size();
    bool consistent = 1;
    for (int i = 0; i < loopSize && consistent; i++){
        const Code pastGuess = pastGuesses[i].guess;
        const Response pastResponse = pastGuesses[i].response;
        consistent = consistentWithGuess(pastGuess, pastResponse, guess);
    }
    return consistent;
}

//agentGuess
//determines best guess to reduce pool size of consistent guesses
//  IN-- Nill
//  OUT-- CODE
Code Mastermind::agentGuess()const
{
    const vector<int> initialHypotheticalVector(4,0);
    Code candidateCode(initialHypotheticalVector), bestCandidateCode(initialHypotheticalVector);
    float lowestCandidateScore, numberConsistentWithCandidate = 0;
   
    bool consistent, candidateAtMax = 0;
    int candidateCounter=0;
    
    if(pastGuesses.size() != 0){
        while(!candidateAtMax){
            do{
                candidateAtMax = candidateCode.increment();
            }while(!consistentWithPreviousGuesses(candidateCode) && !candidateAtMax);
            candidateCounter++;
            
            numberConsistentWithCandidate = calculateScore(candidateCode);
            
            if( (candidateCounter == 1) || (numberConsistentWithCandidate < lowestCandidateScore) ){
                bestCandidateCode.setCode(candidateCode);
                lowestCandidateScore = numberConsistentWithCandidate;
            }
        }
    }
    return bestCandidateCode;
}

//calculateScore
//returns the score of a potential candidate
//  IN-- Nill
//  OUT-- Int
int Mastermind::calculateScore(const Code candidateCode) const throw (baseException){
    if(candidateCode.getCode().size() != 4){
        throw "Mastermind::calculateScore: Malformed vector.";
    }
    const vector<int> initialHypotheticalVector(4,0);
    Response hypotheticalResponse(0,0);
    int numberConsistentWithCandidate = 0;
    bool consistent, hypotheticalAtMax, responseLoopDone;
    
    do{
        Code hypotheticalConsistentCode(initialHypotheticalVector);
        int numberConsistentWithResponse = 0;
        do{
            consistent = consistentWithGuess(candidateCode, hypotheticalResponse, hypotheticalConsistentCode);
            if(consistent){
                consistent = consistentWithPreviousGuesses(hypotheticalConsistentCode);
            }
            if(consistent) numberConsistentWithResponse ++;
            hypotheticalAtMax = hypotheticalConsistentCode.increment();
        }while(!hypotheticalAtMax);
        
        if (numberConsistentWithResponse > numberConsistentWithCandidate){
            numberConsistentWithCandidate = numberConsistentWithResponse;
        }
        responseLoopDone = hypotheticalResponse.increment();
    }while(!responseLoopDone);
    return numberConsistentWithCandidate;
}

//Operator Overload <<
//overloads the << operator for members of Mastermind class data types, for printing purposes of the secret code.
//  IN-- (Ostream, CLASS)
//  Out-- Ostream
ostream &operator <<(ostream &ostr, const Mastermind &game)
{
    ostr << game.secretCode;
    return ostr;
}

