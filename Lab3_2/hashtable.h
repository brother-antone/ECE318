#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "binaryplaces.h"
#include <fstream>


using namespace std;

class HashTable {

private:
    fstream stored;
    fstream hash;
    fstream link;

    const int maxHashSize = 26000;
    unsigned int hashFun(const char* arr, int size = 22);
    void initializeFile(fstream& fileStream);

public:
    HashTable();
    ~HashTable();
    void add_to(int index, binaryplace *bp);
};

#endif
