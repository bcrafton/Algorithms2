// code.cpp
// the code class for the mastermind game
// Brian Crafton and Oliver Scott.
#include "code.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

#define CODE_SIZE 4

//default constructor
//  IN -- Nill
//  OUT -- Code Object
Code::Code()
{
}
//Constructor(vector<int> codeVector)
// constructs a code object and sets the vector to the given vector
//  IN -- CODE
//  OUT -- Int
Code::Code(vector <int> codeVector)
{
	this->code = codeVector;
}
//generateCode
//randomizes a new value for data member storedCode. makes use of the rand function supplied by <stdlib>,
//and seeds the random position with the computers generated clocktime.
//  IN- Nill
//  OUT- Nill
void Code::generateCode()
{
	code.empty();

	srand (time(NULL));
	for(int counter = 0; counter < CODE_SIZE; counter++)
	{
		this->code.push_back(rand()%6);
	}
}
//checkCorrect
//compares the supplied CODE with the data member storedCode, and determines number of integers in
//matching positions.
//  IN -- CODE
//  OUT -- Int
int Code::checkCorrect(const Code &otherCode) const
{
	int correctNumberCount = 0;
	for(int counter = 0; counter < CODE_SIZE; counter++)
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
//  IN -- CODE
//  OUT -- Int
int Code::checkIncorrect(const Code &guess) const
{
    int incorrectCounter = 0;
    bool foundMatch[4] = {0, 0, 0, 0};
    const int searchLimit = code.size();
    const vector<int> guessCode = guess.code;
    
    for(int i=0; i<searchLimit; i++)
	{
        for(int j=0; j<searchLimit; j++)
		{
            if( !foundMatch[i] && (code[i]==guessCode[j]) )
			{
                if( (i!=j) && (code[i] != guessCode[i]) )
				{
                    incorrectCounter++;
                    foundMatch[i] = 1;
                }
                break;
            }
        }
    }
    return incorrectCounter;
}
//printCode
// prints the code vector to the screen
//  IN -- Nill
//  OUT -- Nill
void Code::printCode() const
{
	for(int counter = 0; counter < CODE_SIZE; counter++)
	{
		cout << this->code[counter];
	}
}
//setStoredCode
// sets the stored code in the code object
//  IN -- Nill
//  OUT -- Nill
void Code::setStoredCode(const vector<int> code)
{
	this->code = code;
}



