#include "hashtable.h"

using namespace std;

HashTable::HashTable() : maxHashSize(26000) {
	inistializeFile(hashtable);
}

HashTable::~HashTable(){              // You will need to change this at some point
	writePlaces.close();
	hashtable.close();
	link.close();
}


unsigned int HashTable::hashFun(const char* arr, int size = 22) {
       unsigned int hashVal = 0;
	for (int i = 0; i < size; i++){
	 	char c = arr[i];
		hashVal = hashVal * 31 + c;
	}
	return hashVal % maxHashSize;
}

void HashTable::inistializeFile(fstream &fileStream) {
	fileStream.seekp(0, ios::beg);

	int nullVal =  -1;
	const int times = 26000;

	for(int i = 0; i < times; i++){
		fileStream.write((char *) &nullVal, sizeof(int));
	}
}

/*void HashTable::addto(fstream file1, fstream file2, int index, binaryplace bp) {
	int key = hashFun(bp.name);
	int val = -1;
*/
	//write link struct to link file
	//write to key value index of hash
	

	
}



