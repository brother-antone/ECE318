#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "base28.cpp"
#include "binaryplaces.h"
#include <iostream>
#include <fstream>
//#include <string.h>

using namespace std;

class HashTable {

private:
	fstream stored;
	fstream hash;
	fstream link;

	const int maxHashSize;
	unsigned int hashFun(const char* arr, int size = 22);
	void initializeFile(fstream& fileStream);

public:
	HashTable();
	~HashTable();
	void add_to(int index, binaryplace *bp);
};

#endif
