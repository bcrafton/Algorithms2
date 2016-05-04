/**
 * board.cpp
 * Brian Crafton and Oliver Scott
 * The board object for storing the sudoku board
 *
 */

#include "board.h"

/**
 * the board constructor, sets the conflicts arrays
 */
board::board(int sqSize)
   : value(BoardSize, BoardSize)
// Board constructor
{
	numberSolveCalls = 0;
	this->columnConflicts.resize(9, *(new vector<int>(9)));
	this->rowConflicts.resize(9, *(new vector<int>(9)));
	this->squareConflicts.resize(9, *(new vector<int>(9)));
}

/**
 * clears the board and clears the conflicts arrays
 */
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

/**
 * initializes the board from a ifstream object
 * changed so that it reads in the sudoku puzzle from 0-8 rather than 1-9
 * this change was made here : 'editBoard(i, j, ch-'1');' from editBoard(i, j, ch-'0');
 */
void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   numberSolveCalls = 0;
   char ch;

   clear();
   for (int i = 0; i < BoardSize; i++)
   {
	   for (int j = 0; j < BoardSize; j++)
	   {
		   fin >> ch;
	       // If the read char is not Blank
	       if (ch != '.')
	       {
	    	   editBoard(i, j, ch-'1');
	       }
	       else
	       {
	    	   setCell(i, j, -1);
	       }
	   }
   }
}

/**
 * initializes the board from a filename
 * changed so that it reads in the sudoku puzzle from 0-8 rather than 1-9
 * this change was made here : 'editBoard(i, j, ch-'1');' from editBoard(i, j, ch-'0');
 */
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
   for (int i = 0; i < BoardSize; i++)
   {
      for (int j = 0; j < BoardSize; j++)
      {
    	  fin >> ch;
    	  // If the read char is not Blank
    	  if (ch != '.')
    	  {
    		  editBoard(i, j, ch-'1');
    	  }
    	  else
    	  {
    		  setCell(i, j, -1);
    	  }
      }
   }
}

/**
 * sets a cell in the board and handles the conflicts arrays
 */
void board::editBoard(int x, int y, int value)
{
	setCell(x,y,value);
	updateConflicts(x,y,value);
}

/**
 * clears a cell, and hadnles the conflicts arrays
 */
void board::clearCell(int x, int y)
{
	int temp = this->value[x][y];
	this->value[x][y] = -1;

	// need to subtract 1 since array indices start at 0, sodoku entities start at 1
	this->columnConflicts[getColumn(x,y)][temp]--;
	this->rowConflicts[getRow(x,y)][temp]--;
	this->squareConflicts[getSquare(x,y)][temp]--;
}

/**
 * sets a cell
 */
void board::setCell(int x, int y, int value)
{
	this->value[x][y] = value;
}

/**
 * gets the column from a 2-d point
 */
int board::getColumn(int x, int y) const
{
	return y;
}

/**
 * gets the row from a 2-d point
 */
int board::getRow(int x, int y) const
{
	return x;
}

/**
 * gets the square from a 2-d point
 */
int board::getSquare(int x, int y) const
{
	return 3 * int(x/3) + int(y/3);
}

/**
 * updates the conflicts arrays based on a value added to the board
 */
void board::updateConflicts(int x, int y, int value)
{
	// need to subtract 1 since array indices start at 0, sodoku entities start at 1
	this->columnConflicts[getColumn(x,y)][value]++;
	this->rowConflicts[getRow(x,y)][value]++;
	this->squareConflicts[getSquare(x,y)][value]++;
}

/**
 * overloaded operator for a vector of integers
 */
ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < v.size(); i++)
      ostr << v[i] << " ";
   ostr << endl;
   return ostr;
}

/**
 * returns the value stored in the given cell
 */
ValueType board::getCell(int i, int j) const
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 0 && i < BoardSize && j >= 0 && j < BoardSize) // shud be >= 0 and should be less than boardsize
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

/**
 * checks if the cell is blank or not.
 */
bool board::isBlank(int i, int j) const
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 0 || i >= BoardSize || j < 0 || j >= BoardSize) // shud not be < 0 and should not be boardsize or greater
      throw rangeError("bad value in setCell");

   return getCell(i, j) == -1;
}

/**
 * prints the board
 */
void board::print() const
// Prints the current board.
{
	for (int i = 0; i < BoardSize; i++)
	{
		if (i % SquareSize == 0)
		{
			cout << " -";
			for (int j = 0; j < BoardSize; j++){cout << "---";}
			cout << "-";
			cout << endl;
		}
      for (int j = 0; j < BoardSize; j++)
      {
    	  if (j % SquareSize == 0)
    		  cout << "|";
    	  if (!isBlank(i,j))
    		  cout << " " << getCell(i,j)+1 << " ";
    	  else
    		  cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 0; j < BoardSize; j++){cout << "---";}
   cout << "-";
   cout << endl;
}

/**
 * prints the conflicts on the board
 */
void board::printConflicts()
{
	cout << "Column Conflicts:" << endl;
	cout << columnConflicts;
	cout << "Row Conflicts:" << endl;
	cout << rowConflicts;
	cout << "Square Conflicts:" << endl;
	cout << squareConflicts;
}

/**
 * checks if the sudoku puzzle has been solved
 */
bool board::solved()
{
	const int nRows = this->value.getRowCount();
	const int nCols = this->value.getColumnCount();

	for(int rowCounter = 0; rowCounter < nRows; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < nCols; columnCounter++)
		{
			if(this->value[rowCounter][columnCounter] == -1)
			{
				return false;
			}
		}
	}
	return (containsOnly(columnConflicts, 1) && containsOnly(rowConflicts, 1) && containsOnly(squareConflicts, 1));
}

/**
 * overloaded operator for a vector of vectors of integers.
 */
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

/**
 * checks if a vector of integers contains only the given value
 */
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

/*
 * checks a vector of vectors of integers contains only the given value
 */
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

/**
 * returns a emtpy index
 */
bool board::hasEmptyCell() const
{
    for (int row = 0; row < BoardSize; row++)
    {
        for (int col = 0; col < BoardSize; col++)
        {
            if (value[row][col] == -1)
            {
            	return true;
            }
        }
    }
    return false;
}

/**
 * sets the row and col value equal to the cell with the lowest number of possible solutions
 */
int board::lowestNumberSolutions(int &row, int &col)
{
	int numberSolutions = 0;
	int leastNumberSolutions = BoardSize+1;
	for(int rowCounter = 0; rowCounter < BoardSize; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < BoardSize; columnCounter++)
		{
			if(isBlank(rowCounter, columnCounter))
			{
				numberSolutions = numberOfSolutions(rowCounter, columnCounter);
				if(leastNumberSolutions > numberSolutions)
				{
					leastNumberSolutions = numberSolutions;
					row = rowCounter;
					col = columnCounter;
				}
			}
		}
	}
	return leastNumberSolutions;
}

/**
 * gets the number of solutions for a cell
 */
int board::numberOfSolutions(int row, int col)
{
	int count = 0;
	for(int cellValue = 0; cellValue < BoardSize; cellValue++)
	{
		if(columnConflicts[getColumn(row, col)][cellValue] || rowConflicts[getRow(row, col)][cellValue] || squareConflicts[getSquare(row, col)][cellValue])
		{
			count++;
		}
	}
	return BoardSize-count;
}

/**
 * checks if the value is in the given row
 */
bool board::inRow(int row, int gameValue) const
{
	for(int columnCounter = 0; columnCounter < BoardSize; columnCounter++ )
	{
		if(value[row][columnCounter] == gameValue)
		{
			return true;
		}
	}
	return false;
}

/**
 * checks if the value is in the given column
 */
bool board::inCol(int col, int gameValue) const
{
	for(int rowCounter = 0; rowCounter < BoardSize; rowCounter++ )
	{
		if(value[rowCounter][col] == gameValue)
		{
			return true;
		}
	}
	return false;
}

/**
 * checks if the value is in the given square
 */
bool board::inSquare(int row, int col, int gameValue) const
{
	int square = getSquare(row, col);
	int rowOffset = 3 * (square / 3);
	int columnOffset = 3 * (square % 3);

	for(int rowCounter = 0; rowCounter < 3; rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < 3; columnCounter++)
		{
			if(value[rowCounter + rowOffset][columnCounter + columnOffset] == gameValue)
			{
				return true;
			}
		}
	}
	return false;
}

/**
 * checks if the move is a valid move
 */
bool board::validMove(int row, int col, int gameValue) const
{
    return !inRow(row, gameValue) && !inCol(col, gameValue) && !inSquare(row, col, gameValue);
}

/**
 * solves the sudoku puzzle
 */
bool board::solve()
{
	numberSolveCalls++;

    int row, col;

    if (!hasEmptyCell())
       return true;

    lowestNumberSolutions(row, col);

    for (int gameValue = 0; gameValue < BoardSize; gameValue++)
    {
        if (validMove(row, col, gameValue))
        {
            editBoard(row, col, gameValue);
            if (solve())
                return true;

            clearCell(row, col);
        }
    }
    return false;
}

/**
 * returns the number of times solve has been called.
 */
int board::getNumberSolveCalls() const
{
	return this->numberSolveCalls;
}
