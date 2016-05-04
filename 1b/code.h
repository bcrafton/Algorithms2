// code.h
// the header file for code.cpp
// Brian Crafton and Oliver Scott.

#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <vector>
#include "response.h"
#include "d_except.h"
using namespace std;
// CODE: Stores sequence of numbers of for code

class Code
{
private:
    vector<int> code;
public:
    //Setters,Getters,Constructors
    Code();
    Code(vector<int> seedVector) throw(baseException);
    void setStoredCode(const vector<int> code) throw(baseException);
    void setCode(const Code &newCode) throw(baseException);
    vector<int> getCode() const;

    
    //Functions
    void generateCode();
    int checkCorrect(const Code &otherCode) const throw(baseException);
    int checkIncorrect(const Code &otherCode) const ;
    void printCode() const;
    bool increment();
    friend ostream &operator <<(ostream &ostr, const Code &printCode);
};
#endif
