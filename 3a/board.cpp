/*
 * Board.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: Brian
 */

#include "board.h"

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
	this->columnConflicts.resize(9, *(new vector<int>(9)));
	this->rowConflicts.resize(9, *(new vector<int>(9)));
	this->squareConflicts.resize(9, *(new vector<int>(9)));
}

void board::clear()
{
	const int nRows = this->value.getRowCount();
	const int nCols = this->value.getColumnCount();

	for(int rowCounter = 0; rowCounter < nRows; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < nCols; columnCounter++)
		{
			this->value[rowCounter][columnCounter] = -1;
		}
	}
	this->columnConflicts.clear();
	this->rowConflicts.clear();
	this->squareConflicts.clear();

	// clear clears all the embedded vectors to empty vectors.
	this->columnConflicts.resize(9, *(new vector<int>(9)));
	this->rowConflicts.resize(9, *(new vector<int>(9)));
	this->squareConflicts.resize(9, *(new vector<int>(9)));
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   for (int i = 1; i <= BoardSize; i++)
   {
	   for (int j = 1; j <= BoardSize; j++)
	   {
		   fin >> ch;
	       // If the read char is not Blank
	       if (ch != '.')
	       {
	    	   editBoard(i, j, ch-'0');
	       }
	       else
	       {
	    	   setCell(i, j, -1);
	       }
	   }
   }
}

void board::initialize(string filename)
// Read a Sudoku board from the input file.
{
	ifstream fin;

	fin.open(filename.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << filename << endl;
	    exit(1);
	}

   char ch;

   clear();
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
    	  fin >> ch;
    	  // If the read char is not Blank
    	  if (ch != '.')
    	  {
    		  editBoard(i, j, ch-'0');
    	  }
    	  else
    	  {
    		  setCell(i, j, -1);
    	  }
      }
   }
}

void board::editBoard(int x, int y, int value)
{
	setCell(x,y,value);
	updateConflicts(x,y,value);
}

void board::clearCell(int x, int y)
{
	int temp = this->value[x][y];
	this->value[x][y] = -1;

	// need to subtract 1 since array indices start at 0, sodoku entities start at 1
	this->columnConflicts[getColumn(x,y)][temp - 1]--;
	this->rowConflicts[getRow(x,y)][temp - 1]--;
	this->squareConflicts[getSquare(x,y)][temp - 1]--;
}

void board::setCell(int x, int y, int value)
{
	this->value[x][y] = value;
}

int board::getColumn(int x, int y)
{
	return y-1;
}

int board::getRow(int x, int y)
{
	return x-1;
}

int board::getSquare(int x, int y)
{
	return 3 * int((x-1)/3) + int((y-1)/3);
}

void board::updateConflicts(int x, int y, int value)
{
	// need to subtract 1 since array indices start at 0, sodoku entities start at 1
	this->columnConflicts[getColumn(x,y)][value - 1]++;
	this->rowConflicts[getRow(x,y)][value - 1]++;
	this->squareConflicts[getSquare(x,y)][value - 1]++;
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < v.size(); i++)
      ostr << v[i] << " ";
   ostr << endl;
   return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   return getCell(i, j) == -1;
}

void board::print()
// Prints the current board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		if ((i-1) % SquareSize == 0)
		{
			cout << " -";
			for (int j = 1; j <= BoardSize; j++){cout << "---";}
			cout << "-";
			cout << endl;
		}
      for (int j = 1; j <= BoardSize; j++)
      {
    	  if ((j-1) % SquareSize == 0)
    		  cout << "|";
    	  if (!isBlank(i,j))
    		  cout << " " << getCell(i,j) << " ";
    	  else
    		  cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++){cout << "---";}
   cout << "-";
   cout << endl;
}

void board::printConflicts()
{
	cout << "Column Conflicts:" << endl;
	cout << columnConflicts;
	cout << "Row Conflicts:" << endl;
	cout << rowConflicts;
	cout << "Square Conflicts:" << endl;
	cout << squareConflicts;
}

bool board::validMove(int x, int y, int value)
{
	return ( (columnConflicts[getColumn(x,y)][value] == 0) && (rowConflicts[getRow(x,y)][value] == 0) && (squareConflicts[getSquare(x,y)][value] == 0) );
}

bool board::causesConflicts(int x, int y, int value)
{
	return !validMove(x,y,value);
}

bool board::solved()
{
	const int nRows = this->value.getRowCount();
	const int nCols = this->value.getColumnCount();

	for(int rowCounter = 1; rowCounter < nRows; rowCounter++)
	{
		for(int columnCounter = 1; columnCounter < nCols; columnCounter++)
		{
			if(this->value[rowCounter][columnCounter] == -1)
			{
				return false;
			}
		}
	}
	return (containsOnly(columnConflicts, 1) && containsOnly(rowConflicts, 1) && containsOnly(squareConflicts, 1));
}

ostream& operator<<(ostream& os, vector< vector<int>> &v)
{
    vector<vector<int>>::iterator current;
    vector<vector<int>>::iterator end;

    current = v.begin();
    end = v.end();

    while(current != end)
    {
    	os << *current;
    	current++;
    }
    return os;
}

bool containsOnly(vector<int> &v, int value)
{
	vector<int>::iterator current;
	vector<int>::iterator end;

	current = v.begin();
	end = v.end();

	while(current != end)
	{
		if(*current == value)
		{
			*current++;
		}
		else
		{
			return 0;
		}
	}
	return true;
}

bool containsOnly(vector <vector<int> > &v, int value)
{
	vector<vector<int>>::iterator current;
	vector<vector<int>>::iterator end;

	current = v.begin();
	end = v.end();

	while(current != end)
	{
		if(containsOnly(*current, value))
		{
			current++;
		}
		else
		{
			return false;
		}
	}
	return true;
}

