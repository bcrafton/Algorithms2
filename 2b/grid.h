/**
 * grid.h
 * Brian Crafton and Oliver Scott
 * The grid header file
 *
 */
#ifndef GRID_H_
#define GRID_H_

#include <iostream>
#include <vector>
#include <string>
#include "wordlist.h"
#include "d_matrix.h"
#include "hashtable.h"
using namespace std;

class Grid
{
	private:
		int numberOfRows, numberOfColumns;
	public:
		int numberOfPossibleStringsPerCharacter;
		matrix<char> wordMatrix;
		Grid();
		void loadGrid(string gridFileName) throw(fileOpenError);
		void printGrid();
		int getNumberOfRows() const;
		int getNumberOfColumns() const;

		vector<string> getAllStringsForCharacter(int x, int y);
		void printMatchesByCharacter(WordList &w, int x, int y);
		matrix<char> getAllStringsAt(WordList &w, int x, int y);
		void printMatchesByCharacterHashtable(Hashtable<string> &h, WordList &w, int x, int y);
};

ostream& operator<<(ostream& os, const vector< vector<char> >& v);
ostream& operator<<(ostream& os, const matrix<char> &m);
#endif /* GRID_H_ */
