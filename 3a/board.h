/*
 * Board.h
 *
 *  Created on: Feb 28, 2015
 *      Author: Brian
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

/**
 * The project is setup poorly. The matrix is a 10x10 matrix which means that
 * when u are printing it or checking for the winner u start at the 1 index
 * rather than the 0 index I suppose it makes things a little more readable,
 * but also creates potential for a lot of slip ups and bugs.
 */

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

      void print();
      bool isBlank(int, int);
      ValueType getCell(int, int);
      void printConflicts();
      void setCell(int x, int y, int value);
      void editBoard(int x, int y, int value);
      bool validMove(int x, int y, int value);
      bool causesConflicts(int x, int y, int value);
      void clearCell(int x, int y);
      bool solved();


   private:
      vector<vector<int>> columnConflicts;
      vector<vector<int>> rowConflicts;
      vector<vector<int>> squareConflicts;
      int getColumn(int x, int y);
      int getRow(int x, int y);
      int getSquare(int x, int y);
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
