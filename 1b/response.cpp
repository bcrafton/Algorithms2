// response.cpp
// the response class for the mastermind game
// Brian Crafton and Oliver Scott.
#include "response.h"
#include <iostream>

using namespace std;

//* * * * * * * * * * * * * * * * * * * *
// * * * SETTERS,GETTERS,CONSTRUCTORS * *
//* * * * * * * * * * * * * * * * * * * *

//default constructor
Response::Response()
{
	this->numberCorrect = 0;
	this->numberIncorrect = 0;
}

//seeded constructor
Response::Response(int numberCorrect, int numberIncorrect) throw(rangeError)
{
    if( (numberIncorrect < 0) || (numberCorrect < 0) ){
        throw "Range Error: Response constructor, negative or non integer value(s) proivded.";
    }
	this->numberCorrect = numberCorrect;
	this->numberIncorrect = numberIncorrect;
}

//getNumberCorrect
int Response::getNumberCorrect() const
{
	return this->numberCorrect;
}

//getNumberIncorrect
int Response::getNumberIncorrect() const
{
	return this->numberIncorrect;
}

//setNumberCorrect
void Response::setNumberCorrect(int numberCorrect) throw(rangeError)
{
    if( numberCorrect < 0 ){
        throw "Range Error: Response::setNumberCorrect, negative or non integer value proivded.";
    }
	this->numberCorrect = numberCorrect;
}

//setNumberIncorrect
void Response::setNumberIncorrect(int numberIncorrect) throw(rangeError)
{
    if( numberIncorrect < 0 ){
        throw "Range Error: Response::setNumberIncorrect, negative or non integer value proivded.";
    }
	this->numberIncorrect = numberIncorrect;
}

//* * * * * * * * * * * * * * *
//* * * F U N C T I O N S * * *
//* * * * * * * * * * * * * * *

//printResponse
//prints the RESPONSE data member values
//  IN-- Nill
//  OUT-- Nill
void Response::printResponse() const
{
	cout << "Number of correct: " << this->numberCorrect << endl << "Number of incorrect: " << this->numberIncorrect << endl;
}

//increment
//increments a response and returns whether or not the response cycle has run the defined course. returns true at (2,1).
//designed for the use in a do/while loop
//  IN-- (RESPONSE, RESPONSE)
//  OUT-- Boolean
bool Response::increment(){
    bool done = 0;
    const int n = numberCorrect + numberIncorrect;
    if(n == 0){
        numberIncorrect = 1;
        return done;
    }
    if(numberCorrect == 0){
        numberIncorrect++;
        if(numberIncorrect > 4){
            numberCorrect = 1;
            numberIncorrect = 0;
        }
        return done;
    }
    if(numberIncorrect == 0){
        numberCorrect++;
        if(numberCorrect == 3){
            numberCorrect = 2;
            numberIncorrect = 1;
            return done;
        }
        return done;
    }
    if(n == 4){
        numberCorrect--;
        numberIncorrect++;
        if(numberIncorrect == 4){
            done = 1;
            return done;}
        return done;
    }
    if(n == 3){
        if(numberCorrect == 1){
            numberCorrect = 2;
            numberIncorrect = 2;
            return done;
        }
        numberCorrect = 1;
        numberIncorrect = 2;
        return done;
    }
    return done;
}

//Operator Overload =
//overloads the = operator to allow for ease of assignment for Response objects
//  IN-- Response
//  OUT-- Response
Response &Response::operator=(const Response &otherResponse)
{
    numberCorrect = otherResponse.numberCorrect;
    numberIncorrect = otherResponse.numberIncorrect;
    return *this;
}

//Operator Overload <<
//overloads the ostream operator << to allow for ease of printing the response class
//  IN-- (Ostream, RESPONSE)
//  OUT-- Ostream
ostream &operator <<(ostream &ostr, const Response &printResponse)
{
    ostr << "(" << printResponse.numberCorrect << "," << printResponse.numberIncorrect << ")";
    return ostr;
}

//Operator Overload ==
//overloads the == operator to allow of ease of comparison between two Response objects
//  IN-- (RESPONSE, RESPONSE)
//  OUT-- Boolean
bool operator==(const Response &firstResponse, const Response &secondResponse)
{
    bool areEqual = (firstResponse.numberCorrect == secondResponse.numberCorrect) && (firstResponse.numberIncorrect == secondResponse.numberIncorrect);
    return areEqual;
}
