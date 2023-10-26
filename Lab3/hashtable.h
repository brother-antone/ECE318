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
	void initializeFile(fstream& fileStream);

	// write link file
	// read hashtable
	// write hashtable
public:
	HashTable();
	~HashTable();
	void add_to(int index, binaryplace *bp);
};

#endif
