// code.h
// the header file for code.cpp
// Brian Crafton and Oliver Scott.

#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <vector>

using namespace std;
// CODE: Stores sequence of numbers of for code
class Code
{
	private:
		vector <int> code;
		bool* getBooleanArray();
	public:
		Code();
		Code(vector<int> codeVector);
		void generateCode();
		int checkCorrect(const Code &otherCode) const;
		int checkIncorrect(const Code &otherCode) const;
		void printCode() const;
		void setStoredCode(const vector<int> code);
		
		
};

#endif
