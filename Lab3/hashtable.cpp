#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(){
	stored.open("..\\stored.bin", ios::binary | ios::in | ios::out | ios::trunc);
	hash.open("..\\hash.bin", ios::binary | ios::in | ios::out | ios::trunc);
	link.open("..\\link.bin",ios::binary | ios::in | ios::out | ios::trunc);

	if(stored.fail() || hash.fail() || link.fail())
	{
		cout << "Error opening file(s)" << endl;
	}
	else
	{
		cout << "All files opened. " << endl;
	}
	initializeFile(hash);
	
}

HashTable::~HashTable(){
	if(stored.is_open())
	{
		stored.close();
		if(!stored.is_open())
		{
			cout << "stored file closed." << endl;
		}	
	}
	if(hash.is_open())
	{
		hash.close();
		if(!hash.is_open())
		{
			cout << "hash file closed." << endl;
		}	
	}	
	if(link.is_open())
	{
		link.close();
		if(!link.is_open())
		{
			cout << "link file closed" << endl;
		}	
	}
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

	for(int i = 0; i < maxHashSize; i++){
		fileStream.write((char *) &nullVal, sizeof(int));
	}
}

void HashTable::add_to(int index, binaryplace *bp) {
	stored.write((char *) bp, sizeof(binaryplace));

	int key = hashFun(bp->name);
	int temp;

	hash.seekg(key * sizeof(int), ios::beg);
	hash.read((char *) &temp, sizeof(int));
	
	link.seekp(0, ios::end);
	int val = link.tellp()/sizeof(Link);
	
	hash.seekp(key * sizeof(int), ios::beg);
	hash.write((char *) &val, sizeof(int));

	Link *lk = new Link(index, temp);
	lk->print();
	link.write((char *) lk, sizeof(Link));
}
	

	




