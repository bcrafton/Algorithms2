// response.h
// the header file for response.cpp
// Brian Crafton and Oliver Scott.


#ifndef RESPONSE_H
#define RESPONSE_H

#include "code.h"
#include <iostream>

using namespace std;

// RESPONSE: Generates the response given the guess
class Response
{
	private:
		int numberCorrect;
		int numberIncorrect;
	public:
		Response();
		Response(int numberCorrect, int numberIncorrect);

		int getNumberCorrect() const;
		void setNumberCorrect(int numberCorrect);
		int getNumberIncorrect() const;
		void setNumberIncorrect(int numberIncorrect);
		void printResponse() const;

};

#endif
