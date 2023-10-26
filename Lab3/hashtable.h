#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "base28.cpp"
#include "binaryplaces.cpp"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class HashTable {

private:
	fstream writePlaces;
	fstream hashtable;
	fstream link;

	const int maxHashSize;
	unsigned int hashFun(const char* arr, int size = 22);
	void inistializeFile(fstream& fileStream);

	// write link file
	// read hashtable
	// write hashtable
public:
	HashTable();
	~HashTable();
	// add function
	// search by name function
	// search by state function

};

#endif
