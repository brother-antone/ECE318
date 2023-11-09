#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

//Lab 2 Unique Code
string trim(const string& str) {
    size_t end = str.find("  ");
    if (end != string::npos) {
        return str.substr(0, end);
    }
    else {
        return str;
    }
}

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

    Location(string line) {
        code = stoi(line.substr(0, 8));
        state = line.substr(8, 2);
        name = trim(line.substr(10, 48));
        population = stoi(line.substr(58, 8));
        area = stod(line.substr(66, 14));
        latitude = stod(line.substr(80, 10));
        longitude = stod(line.substr(90, 11));
        intersection = stoi(line.substr(101, 5));
        distance = stod(line.substr(106, 8));
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
        cout << state_name << " " << abbreviation << endl;
    }
};

string getStateName(const string& abbreviation, vector<abb> vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].abbreviation == abbreviation) {
            return vec[i].state_name;
        }
    }
    return "";
}

vector<abb> load_states() {
    string loadin;
    string abbrev;
    string corresponding;

    vector<abb> vec;
    
    ifstream states("..\\Files\\states.txt");
    if (states.fail()) {
        cout << "States abbreviations could not be loaded." << endl;
        exit(2);
    }
    else {
        while (getline(states, loadin)) {
            vec.push_back(abb(loadin.substr(0, 2), loadin.substr(2)));
        }
    }
    return vec;
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

    void n_find(const string& name, vector<abb> vec) {
        size_t index = hash(name);
        size_t startIndex = index;
        bool looped = false;
        bool found = false;
        while (looped == false || index != startIndex) {
            if (table[index] && table[index]->name == name) {
                cout << getStateName(table[index]->state, vec) << " " << table[index]->state << endl;
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
        //temp->print();
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

        while((!(cin >> ext) || ext > temp->R.size()) && ext != -1)
        {
            cin.clear();
            cin.ignore();
            cout << "Enter valid exit number" << endl << "> ";
        }

        if(ext == -1)
        {
            exit(0);
        }
        else
        {
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
    
}

int findInter(Location * loc)
{
    for(int j = 0; j < I.size(); j++)
    {
        if(loc->name == I[j]->name && loc->state == I[j]->state)
        {
            return j;
        }
    }
    return -1;
}

int main()
{
    DynamicHashTable hashTable;
    int index;
    readInter("..\\Files\\intersections.txt");
    readRoads("..\\Files\\connections.txt");

    string input;
    string input_s;
    vector<abb> vec = load_states();
    
    ifstream fin;
    fin.open("C:\\Users\\lanto\\Documents\\Rider\\ECE318\\Files\\named-places.txt");
    if (fin.fail()) {
        cout << "File could not be opened." << endl;
        exit(1);
    }
    else
    {
        string line;
        while (getline(fin, line))
        {
            hashTable.insert(Location(line));
        }
    }
    fin.close();

    
    cout << "What city/town will you start at?" << endl;
    cout << "> ";
    getline(cin, input);
    cout << endl;
    hashTable.n_find(input, vec);
    cout << endl;
    
    cout << "> ";
    cin >> input_s;

    Location* loc = hashTable.s_find(input, input_s);
    if (loc) {
        index = findInter(loc);
        if(index > -1)
        {
            traverse(index); 
        }
        else
        {
            cout << input << " " << input_s << " not found." << endl;
        }
    }
    else {
        cout << "Location not found.";
    }
    cout << endl;


    
    return 0;
}
