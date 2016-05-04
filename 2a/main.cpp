/**
 * Project 2a
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
using namespace std;

void timedSort();
void findMatches(Grid &g, WordList &w);
void search(int sortChoice);


int main()
{
	try{
	timedSort();
	//search(0);
	//search(1);
	//search(2);
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

void timedSort()
{
	string gridFileName;
	cout << "Please enter the name of your grid file: ";
	cin >> gridFileName;

	string wordListFileName = "wordlist.txt";

	Grid g;
	g.loadGrid(gridFileName);

	WordList w;

	w.loadWordList(wordListFileName);
	cout << "starting quick sort" << endl;
	Timer quickSortTimer;
	w.quickSort();
	quickSortTimer.stop();
	cout << "The sort time of quick sort was: " << quickSortTimer.getDuration() << endl;

	w.loadWordList(wordListFileName);
	cout << "starting insertion sort" << endl;
	Timer insertionSortTime;
	w.insertionSort();
	insertionSortTime.stop();
	cout << "The sort time of insertion sort was: " << insertionSortTime.getDuration() << endl;

	w.loadWordList(wordListFileName);
	cout << "starting merge sort" << endl;
	Timer mergeSortTime;
	w.mergeSort();
	mergeSortTime.stop();
	cout << "The sort time of merge sort was: " << mergeSortTime.getDuration() << endl;

	Timer findWordsTime;
	findMatches(g,w);
	findWordsTime.stop();
	cout << "The time to find all the words was: " << findWordsTime.getDuration() << endl;
}
