#include "binaryplaces.h"
#include <iostream>
#include <string>

using namespace std;
  
binaryplace::binaryplace(const string line) { 
    //unique       = stoi(line.substr(0, cd_size));
    area         = stof(line.substr(cd_size + st_size + nm_size + pop_size, ar_size));
    //population   = stoi(line.substr(cd_size + st_size + nm_size, pop_size));
    latitude     = stof(line.substr(cd_size + st_size + nm_size + pop_size + ar_size, latit_size));
    longitude    = stof(line.substr(cd_size + st_size + nm_size + pop_size + ar_size + latit_size, longit_size));
    distance     = stof(line.substr(cd_size + st_size + nm_size + pop_size + ar_size + latit_size + longit_size + intersec_size, dist_size));
    intersection = stoi(line.substr(cd_size + st_size + nm_size + pop_size + ar_size + latit_size + longit_size, intersec_size));
    state[0]     = line[cd_size];
    state[1]     = line[cd_size+1];
    string s = line.substr(cd_size + st_size, nm_size);
    set_string_length(s, 35);
    big b(s);
    b.to_bytes((char *)name, 22);
    cout << "'" << s << "' -> ";
    b.print_digits();
	//cout << line.substr(0, cd_size) << endl;
	//cout << line.substr(cd_size + st_size + nm_size, pop_size) << endl;
}

Link::Link(int index, int next) {
	i = index;
	n = next;
}
