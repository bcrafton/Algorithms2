/**
 * Project 3b
 * main.cpp
 * Brian Crafton and Oliver Scott
 * the main function
 */

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include "board.h"
#include "timer.h"
using namespace std;

int main()
{
   ifstream fin;
   double boardCount = 0;
   double totalTimeTaken = 0;
   double totalSolveCalls = 0;

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
	  Timer t;
      board b1(SquareSize);
      while (fin && fin.peek() != 'Z')
      {
    	  // keep track of the number of boards solved.
    	  boardCount++;
    	  // restart the timer
    	  t.restart();
    	  // initialize the current board
    	  b1.initialize(fin);
    	  // solve the current board
    	  b1.solve();
    	  // stop the timer
    	  t.stop();
    	  // print the board out
    	  b1.print();
    	  // print the time to solve and the number of recursive calls
    	  cout << "time taken: " << t.getDuration() << " | number of solve calls: " << b1.getNumberSolveCalls() << endl;
    	  // track total time taken and total number of recursive calls
    	  totalTimeTaken += t.getDuration();
    	  totalSolveCalls += b1.getNumberSolveCalls();
      }
      // print the average time taken and the average number of recursive calls
      cout << "--------------------------------------------------------\n" ;
      cout << "average solve time: " << (double)(totalTimeTaken/boardCount) << " | average solve calls: " << (double)(totalSolveCalls/boardCount) << endl;

   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}
