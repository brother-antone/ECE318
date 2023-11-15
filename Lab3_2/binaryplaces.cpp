#include "binaryplaces.h"
#include <iostream>
#include <string>

using namespace std;
  
binaryplace::binaryplace(const string line) { 
    unique       = stoi(line.substr(0, cd_size));
    area         = stof(line.substr(cd_size + st_size + nm_size + pop_size, ar_size));
    population   = stoi(line.substr(cd_size + st_size + nm_size, pop_size));
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
}

binaryplace::binaryplace()
{
    memset(name, 0, sizeof(name));
    state[0] = '\0';
    state[1] = '\0';
    unique = 0;
    population = 0;
    intersection = 0;
    area = 0.0;
    latitude = 0.0;
    longitude = 0.0;
    distance = 0.0;
}

Link::Link(int index, int next) {
    i = index;
    n = next;
}

void Link::print()
{
    cout << "Index: " << i << ", Next: " << n << endl;
}
