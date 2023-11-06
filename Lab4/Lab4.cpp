#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

//Lab 2 Unique Code
/*
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
*/

struct Location {
    string state;
    string name;
    double area;
    double latitude;
    double longitude;
    int intersection;
    double distance;

    Location(string s = " ", string n = " ",double a = 0.0, double lat = 0.0, double longi = 0.0, int inter = 0, double d = 0.0) {
        state = s;
        name = n;
        area = a;
        latitude = lat;
        longitude = longi;
        intersection = inter;
        distance = d;
    }

    void print() {
        cout << state << " ";
        cout << name << " ";
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



// Lab 4 Unique Code
const double pi = acos(-1.0);
const string dirs[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW", "N" };

struct intersection;
struct road;

vector <intersection*> I;

struct intersection
{
    int index;
    double longi;
    double lati;
    float dist;
    string state;
    string name;

    vector<road*> R;
    
    intersection(int i, double lo, double la, float d, string s, string n)
    {
        index = i;
        longi = lo;
        lati = la;
        dist = d;
        state = s;
        name = n;
    }

    void print()
    {
        cout << index << " " << longi << " " << lati << " " << dist << " " << state << " " << name << endl;
    }
};

struct road
{

    string name;
    string type;
    intersection * a;
    intersection * b;
    double length;

    road(string n, string t, intersection * a1, intersection * b1, double l)
    {
        name = n;
        type = t;
        a = a1;
        b = b1;
        length = l;
    }

    void print()
    {
        cout << name << " " << type << " " << endl;
        cout << "Intersection A: ";
        a->print();
        cout << "Intersection B: ";
        b->print();
        cout << length << endl;
        
    }
    
};

void readInter(const string &file1)
{
    ifstream fin1;
    fin1.open(file1);
    int idx = 0;

    double lo;
    double la;
    float d;
    string s;
    string n;
    
    if(fin1.fail())
    {
        cout << "Error opening " << file1 << endl;
        return;
    }

    while(fin1 >> lo >> la >> d >> ws)
    {
        getline(fin1, s, ' ');
        getline(fin1, n);
        
        intersection * i = new intersection(idx, lo, la, d, s, n);
        I.push_back(i);
        idx++;
    }
    
    fin1.close();
    cout << file1 << " read successful" << endl;
}

void readRoads(const string &file2)
{
    ifstream fin2;
    fin2.open(file2);

    string n;
    string t;
    int a;
    int b;
    double l;

    if(fin2.fail())
    {
        cout << "Error opening " << file2 << endl;
        return;
    }

    while(fin2 >> n >> t >> a >> b >> l)
    {
        road * r = new road(n , t, I[a], I[b], l);
        I[a]->R.push_back(r);
        I[b]->R.push_back(r); // Idk if this is what the code needs
    }

    fin2.close();
    cout << file2 << " read successful" << endl;
}

string dirfromto(double longitude1, double latitude1, double longitude2, double latitude2)
    { 
    double d = atan2(longitude2 - longitude1, latitude2 - latitude1) * 180.0 / pi + 22.5;
    if (d < 0)
        d += 360.0;
    int n = (int)(d / 45.0);
    return dirs[n];
    }


void traverse(int index)
{
    int ext;
    cout << "Starting intersection number: " << index << endl;

    intersection * temp = I[index];
    
    while(temp != nullptr)
    {
        temp->print();
        for(int i = 0; i < temp->R.size(); i++)
        {
            string dir = dirfromto(temp->R[i]->a->longi, temp->R[i]->a->lati, temp->R[i]->b->longi, temp->R[i]->b->lati);
            string oppdir = dirfromto(temp->R[i]->b->longi, temp->R[i]->b->lati, temp->R[i]->a->longi, temp->R[i]->a->lati);
            if(temp->index == temp->R[i]->a->index)
            {
                cout << "Exit " << i+1 << ": " << temp->R[i]->name << ", ";
                cout << temp->R[i]->length << " miles " << dir << " to intersection #" << temp->R[i]->b->index;
                cout << ", " << temp->R[i]->b->dist << " miles from " << temp->R[i]->b->name << endl;
            }
            else
            {
                cout << "Exit " << i+1 << ": " << temp->R[i]->name << ", ";
                cout << temp->R[i]->length << " miles " << oppdir << " to intersection #" << temp->R[i]->a->index;
                cout << ", " << temp->R[i]->a->dist << " miles from " << temp->R[i]->a->name << endl;
            }
        }
        cout << "Which exit will you take?" << endl;
        cout << "> ";
        cin >> ext ;
        
        if(temp->index == temp->R[ext-1]->a->index)
        {
            temp = temp->R[ext-1]->b;
        }
        else
        {
            temp = temp->R[ext-1]->a;   
        }
    }
    
}

int main()
{
    int index; 
    readInter("C:\\Users\\lanto\\Documents\\Rider\\ECE318\\Files\\intersections.txt");
    readRoads("C:\\Users\\lanto\\Documents\\Rider\\ECE318\\Files\\connections.txt");

    cout << "What intersection will you start at?" << endl;
    cout << "> ";
    cin >> index;

    traverse(index);
    
    return 0;
}
