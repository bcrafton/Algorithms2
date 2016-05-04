/**
 * board.h
 * Brian Crafton and Oliver Scott
 * The board header
 *
 */
#ifndef BOARD_H_
#define BOARD_H_


#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

//int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
   public:
      board(int);
      void clear();

      void initialize(ifstream &fin);
      void initialize(string filename);

      void print() const;
      bool isBlank(int, int) const;
      ValueType getCell(int, int) const;
      void printConflicts();
      void setCell(int x, int y, int value);
      void editBoard(int x, int y, int value);
      void clearCell(int x, int y);
      bool solved();

      bool hasEmptyCell() const;
      bool inRow(int row, int num) const;
      bool inCol(int col, int num) const;
      bool inSquare(int row, int col, int num) const;
      bool validMove(int row, int col, int num) const;
      bool solve();
      int numberOfSolutions(int row, int col);
      int getNumberSolveCalls() const;
      int lowestNumberSolutions(int &row, int &col);

   private:
      int numberSolveCalls;
      vector<vector<int>> columnConflicts;
      vector<vector<int>> rowConflicts;
      vector<vector<int>> squareConflicts;
      int getColumn(int x, int y) const;
      int getRow(int x, int y) const;
      int getSquare(int x, int y) const;
      void updateConflicts(int x, int y, int value);

      // The following matrices go from 1 to BoardSize in each
      // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)

      matrix<ValueType> value;
};

bool containsOnly(vector <vector<int> > &v, int value);
bool containsOnly(vector<int> &v, int value);

ostream& operator<<(ostream& os, vector< vector<int>> &v);
ostream& operator<<(ostream& os, vector<int> &v);

#endif /* BOARD_H_ */
