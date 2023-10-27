//#include "base28.h"
//#include "binaryplaces.h"
#include "hashtable.h"
#include <iostream>

using namespace std;



int main(){
	ifstream read("..//named-places.txt");
	
	fstream stored("..//writtenPlaces.bin", ios::binary | ios::in | ios::out | ios::trunc);
	fstream hash("..//hash.bin", ios::binary | ios::in | ios::out | ios::trunc); 
	fstream link("..//link.bin",ios::binary | ios::in | ios::out | ios::trunc);

	HashTable ht;
	
	if(!stored.is_open()) { 
		cout << "Stored file could not be opened." << endl;
		return -1;
	}

	else if(!hash.is_open())
	{
		cout << "Hash file could not be opened." << endl;
		return -1;
	}	

	else if(!link.is_open())
	{
		cout << "Link file could not be opened" << endl;
		return -1;
	}	

	else if(!read.is_open())
	{
		cout << "Could not read file named places" << endl;
		return -1;
	}	
	else
	{
		int index = 0;
		string readline;

		while(getline(read, readline))
		{
			binaryplace *bp = new binaryplace(readline);
			stored.write((char *) bp, sizeof(binaryplace));
			ht.add_to(index, bp);
			index++;
		}
	
		stored.close();
		hash.close();
		link.close();

		return 0;
	}	
}
