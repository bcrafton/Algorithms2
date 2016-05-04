// response.h
// the header file for response.cpp
// Brian Crafton and Oliver Scott.


#ifndef RESPONSE_H
#define RESPONSE_H

#include "code.h"
#include "d_except.h"
#include <iostream>

using namespace std;

// RESPONSE: Generates the response given the guess
class Response
{
private:
    int numberCorrect;
    int numberIncorrect;
public:
    //Setters,Getters,Constructors
    Response();
    Response(int numberCorrect, int numberIncorrect) throw(rangeError);
    int getNumberCorrect() const;
    int getNumberIncorrect() const;
    void setNumberCorrect(int numberCorrect) throw(rangeError);
    void setNumberIncorrect(int numberIncorrect) throw(rangeError);
    
    //Functions
    void printResponse() const;
    bool increment();
    Response &operator=(const Response &otherResponse);
    friend bool operator==(const Response &firstResponse, const Response &secondResponse);
    friend ostream &operator <<(ostream &ostr, const Response &printResponse);

};


#endif
