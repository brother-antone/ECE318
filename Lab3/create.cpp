#include "base28.h"
#include "binaryplaces.h"
#include "hashtable.h"

using namespace std;



int main(){
	ifstream read("/home/www/class/een318/named-places.txt");
	
	fstream stored("writtenPlaces.bin", ios::binary | ios::in | ios::out | ios::trunc);
	fstream hash("hash.bin", ios::binary | ios::in | ios::out | ios::trunc); 
	fstream link("link.bin",ios::binary | ios::in | ios::out | ios::trunc);

	if(!stored.is_open() || !hash.is_open() || !link.is_open() || !read.is_open()){
		cout << "A file(s) could not be opened." << endl;
		return -1;
	}

	int index = 0;
	string readline;

	while(getline(read, readline)){
		binaryplace bp(readline);
		stored.write((char *) &bp, sizeof(bp));
		//add(index, bp);
		index++;

 
	//Write data to files
	//use the write function
	
	// For cursor to be put at a specific position in outfile
	// file.seekp(26000*sizeof(binaryplace struct), ios::beg)    ------------------  this is for the hash function (indexing the hash function)

	// then use write function
	// hashtable.write((char* ) &bp, sizeof(bp));
	//
	//
	// Do the same for writePlaces.bin and link.bin
	
	stored.close();
	hash.close();
	link.close();

}
