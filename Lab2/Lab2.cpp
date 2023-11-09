#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>

using namespace std;


struct Location {
    int code;
    string state;
    string name;
    int population;
    double area;
    double latitude;
    double longitude;
    int intersection;
    double distance;

    Location(int c = 0, string s = " ", string n = " ", int p = 0, double a = 0.0, double lat = 0.0, double longi = 0.0, int inter = 0, double d = 0.0) {
        code = c;
        state = s;
        name = n;
        population = p;
        area = a;
        latitude = lat;
        longitude = longi;
        intersection = inter;
        distance = d;
    }

    void print() {
        cout << code << " " << state << " ";
        cout << name << " " << population << " ";
        cout << fixed << setprecision(6) << area << " " << latitude << " " << longitude << " ";
        cout << defaultfloat << intersection << " " << distance << endl;
    }
};

struct abb {
    string abbreviation;
    string state_name;

    abb(string a = "", string s = "") {
        abbreviation = a;
        state_name = s;
    }

    void print() {
        cout << abbreviation << " " << state_name << endl;
    }
};

string getStateName(const string& abbreviation, abb* array, int size = 57) {
    for (int i = 0; i < size; i++) {
        if (array[i].abbreviation == abbreviation) {
            return array[i].state_name;
        }
    }
    return "";
}

abb* load_states() {
    string loadin;
    string abbrev;
    string corresponding;
    int i = 0;

    abb* array = new abb[57];

    ifstream states("C:\\Users\\lanto\\Documents\\Rider\\ECE318\\Files\\states.txt");
    if (states.fail()) {
        cout << "States abbreviations could not be loaded." << endl;
        exit(2);
    }
    else {
        while (getline(states, loadin)) {
            array[i].abbreviation = loadin.substr(0, 2);
            array[i].state_name = loadin.substr(2);
            i++;

        }
    }
    return array;
}

const double loadFactor = 0.7;

class DynamicHashTable {
private:
    vector<Location*> table;
    size_t count;
    size_t hash(const string& key) const {
        size_t h = 0;
        for (char c : key) {
            h = h * 31 + c;
        }
        return h % table.size();
    }

    void rehash() {
        vector<Location*> oldtable = table;
        table = vector<Location*>(2 * table.size(), nullptr);
        count = 0;
        for (Location* loc : oldtable) {
            if (loc) {
                insert(*loc);
            }
        }
    }

public:
    DynamicHashTable(size_t initialSize = 1000) {
        table = vector<Location*>(initialSize, nullptr);
        count = 0;
    }

    void insert(const Location& loc) {
        if (double(count) / table.size() >= loadFactor) {
            rehash();
        }
        size_t index = hash(loc.name);
        while (table[index] != nullptr) {
            index = (index + 1) % table.size();
        }
        table[index] = new Location(loc);
        count++;
    }

    void n_find(const string& name, abb* array) {
        size_t index = hash(name);
        size_t startIndex = index;
        bool looped = false;
        bool found = false;
        while (looped == false || index != startIndex) {
            if (table[index] && table[index]->name == name) {
                cout << table[index]->state << getStateName(table[index]->state, array) << endl;
                found = true;
            }
            index = (index + 1) % table.size();
            if (index == 0) {
                looped = true;
            }
        }
        if (!found) {
                cout << name << " was not found.";
        }
    }

    Location* s_find(const string& name, const string& state) {
        size_t index = hash(name);

        while (table[index] != nullptr && (table[index]->name != name || table[index]->state != state)) {
            index = (index + 1) % table.size();
        }
        if (table[index] && table[index]->name == name && table[index]->state == state) {
            return table[index];
        }
        else {
            return nullptr;
        }
    }

    ~DynamicHashTable() {
        for (Location* loc : table) {
            delete loc;
        }
    }
};

const int cd_size = 8;
const int st_size = 2;
const int nm_size = 48;
const int pop_size = 8;
const int ar_size = 14;
const int latit_size = 10;
const int longit_size = 11;
const int intersec_size = 5;
const int dist_size = 8;

string trim(const string& str) {
    size_t end = str.find("  ");
    if (end != string::npos) {
        return str.substr(0, end);
    }
    else {
        return str;
    }
}

int main() {
    int cd;
    string st;
    string nm;
    int pop;
    double ar;
    double latit;
    double longit;
    int intersec;
    double dist;
    DynamicHashTable hashTable;
    string line;
    ifstream fin;
    fin.open("C:\\Users\\lanto\\Documents\\Rider\\ECE318\\Files\\named-places.txt");
    if (fin.fail()) {
        cout << "File could not be opened." << endl;
        exit(1);
    }

    else {
        while (getline(fin, line)) {
            cd = stoi(line.substr(0, cd_size));
            st = line.substr(cd_size, st_size);
            nm = trim(line.substr(cd_size + st_size, nm_size));
            pop = stoi(line.substr(cd_size + st_size + nm_size, pop_size));
            ar = stod(line.substr(cd_size + st_size + nm_size + pop_size, ar_size));
            latit = stod(line.substr(cd_size + st_size + nm_size + pop_size + ar_size, latit_size));
            longit = stod(line.substr(cd_size + st_size + nm_size + pop_size + ar_size + latit_size, longit_size));
            intersec = stoi(line.substr(cd_size + st_size + nm_size + pop_size + ar_size + latit_size + longit_size, intersec_size));
            dist = stod(line.substr(cd_size + st_size + nm_size + pop_size + ar_size + latit_size + longit_size + intersec_size, dist_size));
            hashTable.insert(Location(cd, st, nm, pop, ar, latit, longit, intersec, dist));
        }
    }

    fin.close();
    string input;
    string input_n;
    string input_s;

    abb* array = load_states();

    while (true) {
        cout << "Input a command:" << endl;
        cout << "> ";

        cin >> input;
        if (input == "N" || input == "n") {
            cin.ignore();
            getline(cin, input_n);
            cout << endl << endl;
            hashTable.n_find(input_n, array);
            cout << endl << endl;
        }

        else if (input == "S" || input == "s") {
            cin.ignore();
            getline(cin, input_s);
            string Name = input_s.substr(0, input_s.length() - 3);
            string State = input_s.substr(input_s.length() - 2);
            cout << endl << endl;
            Location* loc = hashTable.s_find(Name, State);
            if (loc) {
                loc->print();
            }
            else {
                cout << "Location not found.";
            }
            cout << endl << endl;

        }

        else if (input == "Q" || input == "q") {
            cout << "Thank you for using the Named Places Database." << endl << endl;
            break;
        }

        else {
            cout << "Invalid command. Please try again." << endl << endl;
        }
    }
}
