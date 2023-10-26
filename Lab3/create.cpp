#include "base28.h"
#include "binaryplaces.h"
#include "hashtable.h"

using namespace std;



int main(){
	ifstream read("..named-places.txt");
	
	fstream stored("..//writtenPlaces.bin", ios::binary | ios::in | ios::out | ios::trunc);
	fstream hash("..//hash.bin", ios::binary | ios::in | ios::out | ios::trunc); 
	fstream link("..//link.bin",ios::binary | ios::in | ios::out | ios::trunc);

	HashTable ht;
	
	if(!stored.is_open() || !hash.is_open() || !link.is_open() || !read.is_open()){
		cout << "A file(s) could not be opened." << endl;
		return -1;
	}

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

}
