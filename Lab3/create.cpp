#include "hashtable.h"

using namespace std;



int main(){
	ifstream read("../Files/named-places.txt");

	HashTable ht("write");
	
		int index = 0;
		string readline;

		while(getline(read, readline))
		{
			binaryplace *bp = new binaryplace(readline);
			ht.add_to(index, bp);
			index++;
		}
	
		return 0;
}
