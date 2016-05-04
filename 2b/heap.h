/**
 * heap.h
 * Brian Crafton and Oliver Scott
 * The heap object for storing the heap
 *
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Heap
{
private:
	vector<T> heap;
	int heapSize;
public:
	Heap();
	Heap(vector<T> v);
	int parent(int n) const;
	int left(int n) const;
	int right(int n) const;
	T getItem(int n)
	{
		return heap[n];
	}

	void swap(vector<T>& heap, int index1, int index2);
	void printHeap();

	void initializeMaxHeap();
	void maxHeapify(vector<T>& heap, int n);
	void buildMaxHeap();

	void initializeMinHeap();
	void minHeapify(vector<T>& heap, int n);
	void buildMinHeap();

	vector<T> heapSortAscending();
	vector<T> heapSortDescending();

};


#include "heap.h"

template <class T>
Heap<T>::Heap(vector<T> v)
{
	this->heap = v;
	heapSize = heap.size();
}

template <class T>
int Heap<T>::parent(int n) const
{
	return n/2;
}

template <class T>
int Heap<T>::right(int n) const
{
	return 2*(n+1);
}

template <class T>
int Heap<T>::left(int n) const
{
	return 2*n+1;
}


template <class T>
void Heap<T>::maxHeapify(vector<T>& heap, int i)
{
	int l = left(i);
	int r = right(i);
	int largest = 0;
	if(l <= heapSize-1 && heap[l] > heap[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}

	if(r <= heapSize-1 && heap[r] > heap[largest])
	{
		largest = r;
	}

	if(largest != i)
	{
		swap(heap, i, largest);
		maxHeapify(heap, largest);
	}
}

template <class T>
void Heap<T>::buildMaxHeap()
{
	heapSize = heap.size();
	for(int i = (heap.size()-1)/2; i >= 0; i--)
	{
		maxHeapify(heap, i);
	}
}

template <class T>
void Heap<T>::swap(vector<T>& heap, int index1, int index2)
{
	T temp = heap[index1];
	heap[index1] = heap[index2];
	heap[index2] = temp;
}

template <class T>
void Heap<T>::printHeap()
{
	const int vectorSize = heap.size();
	for(int counter = 0; counter < vectorSize; counter++)
	{
		cout << + "|" << heap[counter] << "| ";
		cout << endl;
	}

}

template <class T>
vector<T> Heap<T>::heapSortAscending()
{
	buildMaxHeap();

	vector<T> copy = heap;

	const int vectorSize = heap.size();
	for(int counter = vectorSize-1; counter >= 1; counter--)
	{
		swap(copy, 0, counter);
		heapSize--;
		maxHeapify(copy, 0);
	}
	return copy;
}

template <class T>
vector<T> Heap<T>::heapSortDescending()
{
	buildMinHeap();

	vector<T> copy = heap;

	const int vectorSize = heap.size();
	for(int counter = vectorSize-1; counter >= 1; counter--)
	{
		swap(copy, 0, counter);
		heapSize--;
		minHeapify(copy, 0);
	}
	return copy;
}


template <class T>
void Heap<T>::minHeapify(vector<T>& heap, int n)
{
	int l = left(n);
	int r = right(n);
	int smallest = 0;
	if(l <= heapSize-1 && heap[l] < heap[n])
	{
		smallest = l;
	}
	else
	{
		smallest = n;
	}

	if(r <= heapSize-1 && heap[r] < heap[smallest])
	{
		smallest = r;
	}

	if(smallest != n)
	{
		swap(heap, n, smallest);
		minHeapify(heap, smallest);
	}
}

template <class T>
void Heap<T>::buildMinHeap()
{
	heapSize = heap.size();
	for(int i = (heap.size()-1)/2; i >= 0; i--)
	{
		minHeapify(heap, i);
	}
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    const int vectorSize = v.size();

    for(int vectorIndex = 0; vectorIndex < vectorSize; vectorIndex++)
    {
    	cout << + "|" << v[vectorIndex] << "| ";
    }
    os << "\n";
    return os;
}



#endif /* HEAP_H_ */
