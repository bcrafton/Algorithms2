//============================================================================
// Name        : algorithms_hw_3a.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "board.h"
using namespace std;

/**
 * The project is setup poorly. The matrix is a 10x10 matrix which means that
 * when u are printing it or checking for the winner u start at the 1 index
 * rather than the 0 index I suppose it makes things a little more readable,
 * but also creates potential for a lot of slip ups and bugs.
 */

int main()
{
   ifstream fin;

   // Read the sample grid from the file.
   string fileName = "sudoku.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      board b1(SquareSize);
      while (fin && fin.peek() != 'Z')
      {
    	  b1.initialize(fin);
    	  b1.print();
    	  b1.printConflicts();
    	  cout << "The puzzle has been solved: " << b1.solved() << endl;
      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}
