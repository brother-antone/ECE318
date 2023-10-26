#ifndef BINARYPLACES_H
#define BINARYPLACES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include <string.h>
#include "base28.h"

using namespace std;

const int cd_size = 8;
const int st_size = 2;
const int nm_size = 48;
const int pop_size = 8;
const int ar_size = 14;
const int latit_size = 10;
const int longit_size = 11;
const int intersec_size = 5;
const int dist_size = 8;

struct binaryplace{
	char name[22];
	char state[2];
	int unique, population;
	int intersection;
	float area, latitude, longitude, distance;
	binaryplace(const string line);
};

struct Link{
	int i, n;
	Link(int idx, int next);
};


#endif
