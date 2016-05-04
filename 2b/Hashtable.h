/**
 * Hashtable.h
 * Brian Crafton and Oliver Scott
 * The hashtable object for storing the wordlist
 *
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <list>
using namespace std;

template<class T>
class Hashtable
{
// does not recreate vector each time, doubles size each time so not totally inefficient
private:
	vector< list<T>* > hashArray;
	int size;
public:
	Hashtable(int size);
	void add(T key, T value);
	void add(T value);
	int hash(T key);
	bool contains(T value);
	void loadHashtable(vector<T> &v);
	void printMatches(vector<T> v);
	void deleteItem(T item);
};

template<class T>
Hashtable<T>::Hashtable(int size)
{
	this->size = size;
	hashArray.resize(this->size);

	vector< list<T>* >::iterator itr;
	itr = hashArray.begin();

	while(itr != hashArray.end())
	{
		*itr = new list<string>();
		itr++;
	}
}

template<class T>
bool Hashtable<T>::contains(T value)
{
	list<T>* hashIndex = hashArray[hash(value)];
	list<string>::iterator itr;
	itr = hashIndex->begin();

	while(itr != hashIndex->end())
	{
		if(*itr == value)
		{
			return true;
		}
		itr++;
	}
	return false;
}

template<class T>
int Hashtable<T>::hash(T key)
{
	/*
	char c = key[0];
	return c - 'a';
	*/
	std::hash<T> str_hash;
	return str_hash(key) % this->size;
}

template<class T>
void Hashtable<T>::add(T key, T value)
{
	hashArray[hash(key)]->push_back(value);
}

template<class T>
void Hashtable<T>::add(T value)
{
	add(value, value);
}

template<class T>
void Hashtable<T>::loadHashtable(vector<T> &v)
{
	vector<string>::iterator itr;
	itr = v.begin();

	while(itr != v.end())
	{
		add(*itr);
		itr++;
	}
}

template<class T>
void Hashtable<T>::printMatches(vector<T> v)
{
	vector<string>::iterator itr;
	itr = v.begin();

	while(itr != v.end())
	{
		if(contains(*itr))
		{
			cout << *itr;
		}
		itr++;
	}
}

template<class T>
void Hashtable<T>::deleteItem(T item)
{
	list<T>* hashIndex = hashArray[hash(item)];
	list<string>::iterator itr;
	itr = hashIndex->begin();

	while(itr != hashIndex->end())
	{
		if(*itr == item)
		{
			hashIndex->erase(itr);
			return;
		}
		else
		{
			itr++;
		}
	}
}

#endif /* HASHTABLE_H_ */
