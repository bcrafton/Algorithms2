/**
 * wordlist.cpp
 * Brian Crafton and Oliver Scott
 * The wordlist object for storing and sorting the wordlist
 *
 */

#include "wordlist.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

WordList::WordList()
{
}
/*
takes the filename and loads the wordlist into the vector
*/
void WordList::loadWordList(string wordListFileName) throw(fileOpenError)
{
	wordList.clear();
	string line;
	ifstream wordListFile (wordListFileName.c_str());
	if (wordListFile.is_open())
	{
		while ( getline(wordListFile,line) )
	    {
			wordList.push_back(line);
	    }
		wordListFile.close();
	}
	else
	{
		throw fileOpenError("Error loading wordlist. WordList::loadWordList. filename: " + wordListFileName);
	}
}
/*
	prints the wordlist
*/
int WordList::getLongestString() const
{
	int longestStringLength = 0;
	const int wordListLength = this->wordList.size();
	for(int counter = 0; counter < wordListLength; counter++)
	{
		if(wordList[counter].size() > longestStringLength)
		{
			longestStringLength = wordList[counter].size();
		}
	}
	return longestStringLength;
}

void WordList::printWordList() const
{
	cout << wordList ;
}

/*
	method that calls quicksort on the list
*/
void WordList::quickSort()
{
	const int vectorSize = wordList.size();
	quickSort(0, vectorSize-1);
}

/*
	a helper method to quicksort
*/
void WordList::swap(int index1, int index2)
{
	string temp = wordList[index1];
	wordList[index1] = wordList[index2];
	wordList[index2] = temp;
}

/*
	the actual quicksort implementation
*/
void WordList::quickSort(int start, int end)
{
	if (start < end)
	{
		int pivot = partition(start, end);
		quickSort(start, pivot - 1);
		quickSort(pivot + 1, end);
	}
}
/*
	the partition method used by quicksort
*/
int WordList::partition(int start, int end)
{
	int pivot = start;
	string pivotValue = wordList[pivot];

	for (int pivotCounter = start + 1; pivotCounter <= end; pivotCounter++)
	{
		if (wordList[pivotCounter] < pivotValue)
		{
			pivot++;
			swap(pivotCounter, pivot);
		}
	}
	swap(start, pivot);
	return pivot;
}
/*
	binary search implementation
*/
int WordList::binarySearch(string searchItem, int start, int end)
{
	if(start > end)
	{
		return -1;
	}

	int middle = (start+end)/2;
	if(searchItem == wordList[middle])
	{
		return middle;
	}
	else if(searchItem < wordList[middle])
	{
		return binarySearch(searchItem, start, middle-1);
	}
	else
	{
		return binarySearch(searchItem, middle+1, end);
	}
	return -1;
}
/*
	implementation of insertion sort
*/
void WordList::insertionSort()
{
	const int vectorLength = wordList.size();

	int i, j;
	for(i = 1; i < vectorLength; i++)
	{
		j = i;
		while(j > 0 && wordList[j-1] < wordList[j])
		{
			swap(j-1, j);
			j--;
		}
	}
}
/*
	method that calls binary search
*/
int WordList::search(string searchItem)
{
	const int vectorSize = wordList.size();
	return binarySearch(searchItem, 0, vectorSize-1);
}

/*
	merge sort implementation
*/
vector<string> WordList::mergeSort(vector<string>& list)
{
    if(list.size() == 1)
    {
        return list;
    }

    const int middle = list.size()/2;
    vector<string> left, right;

    for(int vertexIndexCounter = 0; vertexIndexCounter < (int)list.size(); vertexIndexCounter++)
    {
    	if(vertexIndexCounter < middle)
    	{
    		left.push_back(list[vertexIndexCounter]);
    	}
    	else
    	{
    		right.push_back(list[vertexIndexCounter]);
    	}
    }

    left = mergeSort(left);
    right = mergeSort(right);

    merge(list, left, right);
    return list;
}
/*
merge sort helper function merge
*/
void WordList::merge(vector<string> &list, const vector<string>& leftVector, const vector<string>& rightVector)
{
	list.clear();
    unsigned leftCounter = 0, rightCounter = 0;

    while(leftCounter < leftVector.size() && rightCounter < rightVector.size())
    {
        if(leftVector[leftCounter] < rightVector[rightCounter])
        {
        	list.push_back(leftVector[leftCounter]);
            leftCounter++;
        }
        else
        {
        	list.push_back(rightVector[rightCounter]);
            rightCounter++;
        }
    }

    while(leftCounter < leftVector.size())
    {
    	list.push_back(leftVector[leftCounter]);
        leftCounter++;
    }

    while(rightCounter < rightVector.size())
    {
    	list.push_back(rightVector[rightCounter]);
        rightCounter++;
    }
}
/*
	calls the merge sort function
*/
void WordList::mergeSort()
{
	mergeSort(wordList);
}
/*
	returns the index at the given index parameter
*/
string WordList::getIndexAt(int index)
{
	return wordList[index];
}
/*
	overloaded << operator for the vector<string>
*/
ostream& operator<<(ostream& os, const vector<string>& v)
{
    const int vectorSize = v.size();
    for(int vectorIndex = 0; vectorIndex < vectorSize; vectorIndex++)
    {
    	os << v[vectorIndex] << "\n";
    }
    return os;
}
/*
	overload << operator for vector<char>
*/
ostream& operator<<(ostream& os, const vector<char>& v)
{
    const int vectorSize = v.size();
    for(int vectorIndex = 0; vectorIndex < vectorSize; vectorIndex++)
    {
    	os << v[vectorIndex] << "\n";
    }
    return os;
}
/*
	overload << operator for a wordlist
*/
ostream& operator<<(ostream& os, const WordList& w)
{
    os << w.wordList;
    return os;
}
