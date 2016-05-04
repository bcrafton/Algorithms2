/*
 /**
 * wordlist.cpp
 * Brian Crafton and Oliver Scott
 * The wordlist object for storing the grid
 *
 */


#ifndef WORDLIST_H_
#define WORDLIST_H_

#include <iostream>
#include <vector>
#include <string>
#include "d_except.h"

using namespace std;

class WordList
{
	private:
		vector<string> wordList;

	public:
		WordList();
		void loadWordList(string wordListFileName) throw(fileOpenError);
		void quickSort();
		// shud be private
		void swap(int index1, int index2);
		int partition(int start, int end);
		void quickSort(int start, int end);

		void insertionSort();

		int getLongestString() const;
		void mergeSort();
		vector<string> mergeSort(vector<string>& vec);
		void merge(vector<string> &vec,const vector<string>& left, const vector<string>& right);

		int search(string searchItem);
		int binarySearch(string searchItem, int start, int end);
		string getIndexAt(int index);
		void printWordList() const;


		friend ostream& operator<<(ostream& os, const WordList& w);
};

ostream& operator<<(ostream& os, const vector<string>& v);



#endif /* WORDLIST_H_ */
