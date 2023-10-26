#include "hashtable.h"

using namespace std;

HashTable::HashTable() : maxHashSize(26000) {
	initializeFile(hashtable);
}

HashTable::~HashTable(){              // You will need to change this at some point
	writePlaces.close();
	hashtable.close();
	link.close();
}


unsigned int HashTable::hashFun(const char* arr, int size) {
       unsigned int hashVal = 0;
	for (int i = 0; i < size; i++){
	 	char c = arr[i];
		hashVal = hashVal * 31 + c;
	}
	return hashVal % maxHashSize;
}

void HashTable::initializeFile(fstream &fileStream) {
	fileStream.seekp(0, ios::beg);

	int nullVal =  -1;
	const int times = 26000;

	for(int i = 0; i < times; i++){
		fileStream.write((char *) &nullVal, sizeof(int));
	}
}

void HashTable::add_to(int index, binaryplace *bp) {
	int key = hashFun(bp->name);
	int temp;

	hashtable.seekg(key * sizeof(int), ios::beg);
	hashtable.read((char *) &temp, sizeof(int));
	
	link.seekp(0, ios::end);
	int val = link.tellp();

	hashtable.seekp(key * sizeof(int), ios::beg);
	hashtable.write((char *) &val, sizeof(int));

	Link *lk = new Link(index, temp);
	
	link.write((char *) lk, sizeof(Link));
}
	

	




