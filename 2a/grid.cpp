/**
 * grid.cpp
 * Brian Crafton and Oliver Scott
 * The grid object for storing the grid
 *
 */
#include "grid.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#define NUMBER_OF_DIRECTIONS 8
#define MIN_NUM_CHARACTERS 5

string vectorToString(vector <char> &v);
vector <string> matrixToStringList(matrix<char> list);

Grid::Grid()
{
}
/*
	takes the filename as a string and loads the file into the grid field
*/
void Grid::loadGrid(string gridFileName) throw(fileOpenError)
{
	ifstream gridFile (gridFileName.c_str());
	if (gridFile.is_open())
	{
		gridFile >> numberOfColumns >> numberOfRows;
		wordMatrix.resize(numberOfRows, numberOfColumns);
		for(int rowCounter = 0; rowCounter < numberOfRows; rowCounter++)
		{
			for(int columnCounter = 0; columnCounter < numberOfColumns; columnCounter++)
			{
				gridFile >> wordMatrix[rowCounter][columnCounter];
			}
		}
	}
	else
	{
		throw fileOpenError("Error loading grid. Grid::loadGrid. filename: " + gridFileName);
	}
}

/*
	prints the grid
*/
void Grid::printGrid()
{
	for(int rowCounter = 0; rowCounter < numberOfRows; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < numberOfColumns; columnCounter++)
		{
			cout << wordMatrix[rowCounter][columnCounter] << " ";
		}
		cout << endl;
	}
}

int Grid::getNumberOfRows() const
{
	return this->numberOfRows;
}

int Grid::getNumberOfColumns() const
{
	return this->numberOfColumns;
}

/*
	gets all the possible strings for the character at location x,y
*/

int numberOfPossibleStrings(int numberOfColumns, int longestWordLength)
{
	if(numberOfColumns - MIN_NUM_CHARACTERS < longestWordLength)
	{
		return numberOfColumns - MIN_NUM_CHARACTERS;
	}
	else
	{
		return longestWordLength;
	}
}

matrix<char> Grid::getAllStringsAt(int x, int y)
{
	matrix<char> allStrings;
	allStrings.resize( (numberOfColumns-MIN_NUM_CHARACTERS)*NUMBER_OF_DIRECTIONS, numberOfColumns);

	for(int vectorIndexCounter = 0; vectorIndexCounter < numberOfColumns-MIN_NUM_CHARACTERS; vectorIndexCounter++)
	{
		for(int stringIndexCounter = 0; stringIndexCounter <= vectorIndexCounter+MIN_NUM_CHARACTERS; stringIndexCounter++)
		{
			allStrings[vectorIndexCounter + 0*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[x][(y + stringIndexCounter)%numberOfColumns];
			allStrings[vectorIndexCounter + 1*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[(x + stringIndexCounter)%getNumberOfRows()][y];
			allStrings[vectorIndexCounter + 2*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[(x + stringIndexCounter)%getNumberOfRows()][(y + stringIndexCounter)%numberOfColumns];
			allStrings[vectorIndexCounter + 3*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[(x + stringIndexCounter)%getNumberOfRows()][((int)abs(y + numberOfColumns - stringIndexCounter))%numberOfColumns];
			allStrings[vectorIndexCounter + 4*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[x][((int)abs(y + numberOfColumns - stringIndexCounter))%numberOfColumns];
			allStrings[vectorIndexCounter + 5*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[((int)abs(x + numberOfColumns - stringIndexCounter))%numberOfColumns][y];
			allStrings[vectorIndexCounter + 6*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[((int)abs(x + numberOfColumns - stringIndexCounter))%numberOfColumns][((int)abs(y + numberOfColumns - stringIndexCounter))%numberOfColumns];
			allStrings[vectorIndexCounter + 7*(numberOfColumns-MIN_NUM_CHARACTERS)][stringIndexCounter] = wordMatrix[((int)abs(x + numberOfColumns - stringIndexCounter))%numberOfColumns][(y + stringIndexCounter)%getNumberOfRows()];
		}
	}
	return allStrings;
}
/*
	prints all the matches found in the wordlist for the char at x, y
*/
void Grid::printMatchesByCharacter(WordList &w, int x, int y)
{
	vector <string> allStrings = matrixToStringList(getAllStringsAt(x,y));
	const int vectorSize = allStrings.size();
	int temp;
	for(int vectorIndexCounter = 0; vectorIndexCounter < vectorSize; vectorIndexCounter++)
	{
		temp = w.search(allStrings[vectorIndexCounter].c_str()); // no idea why c_str() works
		if(temp != -1)
			cout << w.getIndexAt(temp) << endl;
	}
}
/*
	takes a matrix<char> and returns a vector<string>
*/
vector <string> matrixToStringList(matrix<char> list)
{
	const int listSize = list.rows();
	vector <string> stringList(listSize);
	for(int listIndexCounter = 0; listIndexCounter < listSize; listIndexCounter++)
	{
		stringList[listIndexCounter] = vectorToString(list[listIndexCounter]);
	}
	return stringList;
}
/*
	takes a vector<char> and returns a string
*/
string vectorToString(vector <char> &v)
{
	string stringCopy(v.begin(), v.end());
	return stringCopy;
}


/*
	overload operator for <vector<vector<char>>
*/
ostream& operator<<(ostream& os, const vector< vector<char> >& v)
{
    const int vector1Size = v.size();
    const int vector2Size = v[0].size();

    for(int vector1Index = 0; vector1Index < vector1Size; vector1Index++)
    {
    	for(int vector2Index = 0; vector2Index < vector2Size; vector2Index++)
    	{
    		os << v[vector1Index][vector2Index];
    	}
    	os << "\n";
    }
    return os;
}

/*
	overload operator for <vector<vector<char>>
*/
ostream& operator<<(ostream& os, const matrix<char> &m)
{
    const int vector1Size = m.rows();
    const int vector2Size = m[0].size();

    for(int vector1Index = 0; vector1Index < vector1Size; vector1Index++)
    {
    	for(int vector2Index = 0; vector2Index < vector2Size; vector2Index++)
    	{
    		os << m[vector1Index][vector2Index];
    	}
    	os << "\n";
    }
    return os;
}
