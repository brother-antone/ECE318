#include "hashtable.h"
#include <iostream>

using namespace std;



int main(){
	ifstream read("../Files/named-places.txt");

	HashTable ht;
	
		int index = 0;
		string readline;

		while(getline(read, readline))
		{
			binaryplace *bp = new binaryplace(readline);
			ht.add_to(index, bp);
			index++;
		}
		
		ht.~HashTable();
	
		return 0;
}
