/**
 * Project 2b
 * main.cpp
 * Brian Crafton and Oliver Scott
 * the main function and some helpers for running the word search
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include "wordlist.h"
#include "grid.h"
#include "timer.h"
#include <cmath>
#include "time.h"
#include "d_matrix.h"
#include "heap.h"
#include "hashtable.h"
#include <list>
using namespace std;

void timedSort();
void findMatches(Grid &g, WordList &w);
void findMatchesHashtable(Hashtable<string> &h, Grid &g, WordList &w);
void search(int sortChoice);


int main()
{
	try{
	timedSort();
	}
	catch(baseException e)
	{
		cout << e.what();
	}
}
/*
	takes the grid and the wordlist and prints out all the matches by character
*/
void findMatches(Grid &g, WordList &w)
{
	for(int rowCounter = 0; rowCounter < g.getNumberOfRows(); rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < g.getNumberOfColumns(); columnCounter++)
		{
			g.printMatchesByCharacter(w, rowCounter, columnCounter);
		}
	}
}
/*
	takes the grid and the wordlist and prints out all the matches by character
*/
void findMatchesHashTable(Hashtable<string> &h, Grid &g, WordList &w)
{
	for(int rowCounter = 0; rowCounter < g.getNumberOfRows(); rowCounter++)
	{
		for(int columnCounter = 0; columnCounter < g.getNumberOfColumns(); columnCounter++)
		{
			g.printMatchesByCharacterHashtable(h, w, rowCounter, columnCounter);

		}
	}
}
/*
	takes an integer to specify choice of sorting method
	loads the wordlist and the grid
	uses timer object to track the time taken 
	and then sorts and finds all the words in the grid
*/
void search(int sortChoice)
{
	string gridFileName;
	cout << "Please enter the name of your grid file: ";
	cin >> gridFileName;

	WordList w;
	w.loadWordList("wordlist.txt");
	Grid g;
	g.loadGrid(gridFileName);

	Timer sortTime;
	if(sortChoice == 0)
	{
		w.quickSort();
	}
	else if(sortChoice == 1)
	{
		w.insertionSort();
	}
	else if(sortChoice == 2)
	{
		w.mergeSort();
	}
	sortTime.stop();
	cout << "The sort time was: " << sortTime.getDuration() << endl;

	Timer findWordsTime;
	findMatches(g,w);
	findWordsTime.stop();
	cout << "The time to find all the words was: " << findWordsTime.getDuration() << endl;
}
/*
 * Runs and times the 4 sort methods, and searches the 4 grids.
 */
void timedSort()
{
	WordList w;
	Grid g;

	double quickSortTime, heapSortTime, mergeSortTime, insertionSortTime;
	double input15, input30, input50, input250;
	double input15Ht, input30Ht, input50Ht, input250Ht;

	w.loadWordList("wordlist.txt");
	cout << "starting quick sort" << endl;
	Timer quickSortTimer;
	w.quickSort();
	quickSortTimer.stop();
	quickSortTime = quickSortTimer.getDuration();

	w.loadWordList("wordlist.txt");
	cout << "starting heap sort" << endl;
	Timer heapSortTimer;
	w.heapSort();
	heapSortTimer.stop();
	heapSortTime = heapSortTimer.getDuration();

	w.loadWordList("wordlist.txt");
	cout << "starting merge sort" << endl;
	Timer mergeSortTimer;
	w.mergeSort();
	mergeSortTimer.stop();
	mergeSortTime = mergeSortTimer.getDuration();

	insertionSortTime = 0;


	w.loadWordList("wordlist.txt");
	cout << "starting insertion sort" << endl;
	Timer insertionSortTimer;
	w.insertionSort();
	insertionSortTimer.stop();
	insertionSortTime = insertionSortTimer.getDuration();


	Hashtable<string> h(10000);
	h = w.makeHashtable();


	g.loadGrid("input15");
	Timer findWordsTimeInput15;
	findMatches(g,w);
	findWordsTimeInput15.stop();
	input15 = findWordsTimeInput15.getDuration();

	g.loadGrid("input30");
	Timer findWordsTimeInput30;
	findMatches(g,w);
	findWordsTimeInput30.stop();
	input30 = findWordsTimeInput30.getDuration();

	g.loadGrid("input50");
	Timer findWordsTimeInput50;
	findMatches(g,w);
	findWordsTimeInput50.stop();
	input50 = findWordsTimeInput50.getDuration();

	g.loadGrid("input250");
	Timer findWordsTimeInput250;
	findMatches(g,w);
	findWordsTimeInput250.stop();
	input250 = findWordsTimeInput250.getDuration();


	g.loadGrid("input15");
	Timer findWordsTimeInput15Ht;
	findMatchesHashTable(h,g,w);
	findWordsTimeInput15Ht.stop();
	input15Ht = findWordsTimeInput15Ht.getDuration();

	g.loadGrid("input30");
	Timer findWordsTimeInput30Ht;
	findMatchesHashTable(h,g,w);
	findWordsTimeInput30Ht.stop();
	input30Ht = findWordsTimeInput30Ht.getDuration();

	g.loadGrid("input50");
	Timer findWordsTimeInput50Ht;
	findMatchesHashTable(h,g,w);
	findWordsTimeInput50Ht.stop();
	input50Ht = findWordsTimeInput50Ht.getDuration();

	g.loadGrid("input250");
	Timer findWordsTimeInput250Ht;
	findMatchesHashTable(h,g,w);
	findWordsTimeInput250Ht.stop();
	input250Ht = findWordsTimeInput250Ht.getDuration();

	cout << "--------------------------\nSORT TIMES\n--------------------------\n";
	cout << "quick sort time: " << quickSortTime << endl;
	cout << "heap sort time: " << heapSortTime << endl;
	cout << "merge sort time: " << mergeSortTime << endl;
	cout << "insertion sort time: " << insertionSortTime << endl;
	cout << "--------------------------\nSEARCH TIMES\n--------------------------\n";
	cout << "input15: " << input15 << endl;
	cout << "input30: " << input30 << endl;
	cout << "input50: " << input50 << endl;
	cout << "input250: " << input250 << endl;
	cout << "--------------------------\nSEARCH TIMES w/ Hashtable\n--------------------------\n";
	cout << "input15: " << input15Ht << endl;
	cout << "input30: " << input30Ht << endl;
	cout << "input50: " << input50Ht << endl;
	cout << "input250: " << input250Ht << endl;
}
