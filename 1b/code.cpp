// code.cpp
// the code class for the mastermind game
// Brian Crafton and Oliver Scott.
#include "code.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

//* * * * * * * * * * * * * * * * * * * *
// * * * SETTERS,GETTERS,CONSTRUCTORS * *
//* * * * * * * * * * * * * * * * * * * *

//default constructor
Code::Code()
{
    const vector<int> dftVector(4,0);
    code = dftVector;
}

//seeded constructor
Code::Code(vector<int> seedVector) throw (baseException)
{
	if(seedVector.size() != 4)
	{
		throw "Vector not 4 integers long";
	}
	else
	{
		this->code = seedVector;
	}
}

//setStoredCode
void Code::setStoredCode(const vector<int> code) throw (baseException)
{
	if(this->code.size() != 4)
	{
		throw "Vector not 4 integers long";
	}
	else
	{
		this->code = code;
	}
}
//setCode
void Code::setCode(const Code &newCode) throw (baseException)
{
    const vector<int> newCodeValue = newCode.getCode();
    const int vecSize = newCodeValue.size();
    if(vecSize != 4){
        throw "Vector not 4 integers long";
    }
    else{
        for(int i=0; i < vecSize; i++){
            code[i] = newCodeValue[i];
        }
    }
}

//getCode
vector<int> Code::getCode()const
{
    return code;
}

//* * * * * * * * * * * * * * *
//* * * F U N C T I O N S * * *
//* * * * * * * * * * * * * * *

//generateCode
//randomizes a new value for data member storedCode. makes use of the rand function supplied by <stdlib>,
//and seeds the random position with the computers generated clocktime.
//  IN-- Nill
//  OUT-- Nill
void Code::generateCode()
{
	code.empty();
    const int codeSize = 4;
	srand (time(NULL));
	for(int counter = 0; counter < codeSize; counter++)
	{
		this->code.push_back(rand()%6);
	}
}

//checkCorrect
//compares the supplied CODE with the data member storedCode, and determines number of integers in
//matching positions.
//  IN-- CODE
//  OUT-- Int
int Code::checkCorrect(const Code &otherCode) const throw(baseException)
{
	if(otherCode.getCode().size() != 4)
	{
		throw "Vector not 4 integers long";
	}
	const int codeSize = code.size();
	int correctNumberCount = 0;
	for(int counter = 0; counter < codeSize; counter++)
	{
		if(this->code[counter] == otherCode.code[counter])
		{
			correctNumberCount++;
		}
	}
	return correctNumberCount;
}

//checkIncorrect
//compares the supplied CODE with the data member storedCode, and determines number of integers in
//the incorrect positions. ensures no single location is double counted, with the priority of
//correctly placed digits taken into account.
//  IN-- CODE
//  OUT-- Int
int Code::checkIncorrect(const Code &guess)const
{
	if(guess.getCode().size() != 4)
	{
		throw "Vector not 4 integers long";
	}
    int incorrectCounter = 0;
    bool foundMatch[4] = {0,0,0,0};
    bool toBeMatched[4] = {1,1,1,1};
    const unsigned int searchLimit = code.size();
    const vector<int> guessCode = guess.getCode();
    
    for(int i=0; i<searchLimit; i++){
        if(code[i] == guessCode[i]){
            foundMatch[i] = 1;
            toBeMatched[i] = 0;
        }
    }
    for(int i=0; i<searchLimit; i++){
        for(int j=0; j<searchLimit; j++){
            if( ((!foundMatch[i]) && (toBeMatched[j]) && (code[i]==guessCode[j])) ){
                if( (i!=j) && (code[i] != guessCode[i]) ){
                    incorrectCounter++;
                    foundMatch[i] = 1;
                    toBeMatched[j] = 0;
                }
                break;
            }
        }
    }
    return incorrectCounter;
}

//printCode
//prints the code vector to the screen
//  IN-- Nill
//  OUT-- Nill
void Code::printCode() const
{
    const int codeSize = code.size();
	for(int counter = 0; counter < codeSize; counter++)
	{
		cout << this->code[counter];
	}
}

//increment
//increments the value of the stored code. returns true if stored code is already at max value {5,5,5,5}
//  IN-- Nill
//  OUT-- Boolean
bool Code::increment()
{
    const int loopSize = code.size()-1;
    bool carry = 1, done = 0;
    for(int i = loopSize; (i >= 0 ) && carry; i--)
	{
        if( (i==0) && (code[i]==5) )
		{
            code.resize(4);
			code[0] = 5;
			code[1] = 5;
			code[2] = 5;
			code[3] = 5;
            done = 1;
            break;
        }
        else
		{
            code[i]++;
            carry = 0;
            if( code[i]==6 )
			{
                code[i] = 0;
                carry = 1;
            }
        }
    }
    return done;
}

//Operator Overload << 
//overloads the << operator for Vector<Int> data types, for printing purposes. Used in the << overload for the Class definition.
//  IN-- (Ostream, Vector<Int>)
//  Out-- Ostream
ostream &operator<<(ostream &ostr, const vector<int> &printVector)
{
    const int loopLimit = printVector.size();
    for(int i = 0; i < loopLimit; i++){
        ostr << printVector[i];
    }
    return ostr;
}

//Operator Overload <<
//overloads the << operator for members of Code class data types, for printing purposes.
//  IN-- (Ostream, CLASS)
//  Out-- Ostream
ostream &operator<<(ostream &ostr, const Code &printCode)
{
    vector<int> printVector = printCode.code;
    cout << printVector;
    return ostr;
}