#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

const double pi = acos(-1.0);
const int inf = 2147483647;
const string dirs[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW", "N" };
struct intersection;
struct road;
vector <intersection*> I;

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
    
    ifstream states("../Files/states.txt");
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

    bool n_find(const string& name, vector<abb> vec) {
        size_t index = hash(name);
        size_t startIndex = index;
        bool looped = false;
        bool found = false;
        cout << endl << "Possibilities:" << endl;
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
            return false;
        }
        else
        {
            return true;
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

struct intersection
{
    int index;
    double longi;
    double lati;
    float dist;
    string state;
    string name;

    vector<road*> R;

    int weight;
    bool visited;
    intersection * prev;
    
    intersection(int i, double lo, double la, float d, string s, string n, int w = inf, bool v = false, intersection * p = nullptr)
    {
        index = i;
        longi = lo;
        lati = la;
        dist = d;
        state = s;
        name = n;
        weight = w;
        visited = v;
        prev = p;
    }

    void print()
    {
        cout << index << " " << longi << " " << lati << " " << dist << " " << state << " " << name << endl;
        cout << "Weight: " << weight << " " << visited << " " << endl << endl;
    }
};

struct road
{

    string name;
    string type;
    intersection * a;
    intersection * b;
    int length;

    road(string n, string t, intersection * a1, intersection * b1, int l)
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
        cout <<"^^ Length: " << length << endl;
        
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
        int length = (int)(l * 10000);
        road * r = new road(n , t, I[a], I[b], length);
        I[a]->R.push_back(r);
        I[b]->R.push_back(r);
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
        cout << "At intersection #" << temp->index << ", " << temp->dist << " miles from " << temp->name << ", " << temp->state << endl;
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

        while(((!(cin >> ext) || ext > temp->R.size()) || ext == 0) && ext != -1)
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

void search(DynamicHashTable hashTable, vector<abb> vec) {
    int index;
    string input;
    string input_s;

    cout << "What city/town will you start at?" << endl;
    cout << "> ";
    getline(cin, input);
    if(input == "Q" || input == "q")
    {
        exit(0);
    }
    if(!hashTable.n_find(input, vec))
    {
        cout << endl;
        search(hashTable, vec);
    }
    cout << endl << "> ";
    getline(cin, input_s);
    if(input_s == "Q" || input_s == "q")
    {
        exit(0);
    }
    Location* loc = hashTable.s_find(input, input_s);
    if (loc) {
        index = findInter(loc);
        if (index > -1) {
            traverse(index); 
        } else {
            cout << input << " " << input_s << " not found." << endl;
            search(hashTable, vec);
        }
    } else {
        cout << "Location not found." << endl;
        search(hashTable, vec);
    }
    cout << endl;
}

class MinHeap{
private:
  intersection **heapArray;
  int heapSize;
  int capacity;

public:
  MinHeap (int cap);
  ~MinHeap();
  void resize();
  void MinHeapify(int i);
  void bubble(int i);
  void swap(int a, int b);
  void print();  

  int parent(int i){
    return (i-1)/2;
  }

  int left(int i){
    return (i*2) + 1;
  }

  int right(int i){
    return (i*2) + 2;
  }
  
  intersection* getMin(){
    if(heapSize == 0){
      return nullptr;
    }
    else{
      return heapArray[0];
    }
  }

  intersection* extractMin();
  void decreaseKey(intersection *ptr, int newWeight);
  void deleteKey(int i);
  void insertKey(intersection* ptr);
  int findIndex(const intersection* ptr);  
};

MinHeap::MinHeap(int cap){
  capacity = cap;
  heapSize = 0;
  heapArray = new intersection* [capacity];
}

MinHeap::~MinHeap(){
  for(int i = 0; i < heapSize; i++){
    delete heapArray[i];
  }
  delete[] heapArray;
}

void MinHeap::resize(){
  capacity *= 2;

  intersection** newHeapArray = new intersection*[capacity];
  
  for(int i = 0; i < heapSize; i++){
    newHeapArray[i] = heapArray[i];
  }
  delete[] heapArray;
  heapArray = newHeapArray;
}

void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if(l < heapSize && heapArray[l]-> weight < heapArray[smallest]->weight){
        smallest = l;
    }
    if(r < heapSize && heapArray[r]-> weight < heapArray[smallest]->weight){
        smallest = r;
    }
    if(smallest != i){
        swap(smallest, i);
        MinHeapify(smallest);
    }
}    
void MinHeap::bubble(int i){                 
  if(heapSize == 0){
    return;
  }
  else if(i != 0 && heapArray[parent(i)]->weight > heapArray[i]->weight){
    swap(parent(i), i);
    bubble(parent(i));
  }
}

intersection* MinHeap::extractMin(){
  if(heapSize <= 0){
    return nullptr;
  }
  else if(heapSize <= 1){
    heapSize--;
    return heapArray[0];
  }
  else{
    intersection* root = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    MinHeapify(0);
    return root;
  }
}

void MinHeap::swap(int a, int b){
  intersection* temp = heapArray[a];
  heapArray[a] = heapArray[b];
  heapArray[b] = temp;
}

void MinHeap::decreaseKey(intersection* ptr, int newWeight){
    int i = findIndex(ptr);
    heapArray[i]->weight = newWeight;
    bubble(i);
}

void MinHeap::deleteKey(int i){
  if(heapSize == 0){
    return;
  }
  else{
    heapArray[i] = heapArray[heapSize - 1];
    heapSize--;
    bubble(i);
  }
}

void MinHeap::insertKey(intersection * ptr){   
  if(heapSize == capacity){
   resize();
  }
  else if(ptr->visited == false){
    heapArray[heapSize] = ptr;
    int p = parent(heapSize);
    heapSize++;
    bubble(heapSize-1);
  }
    
}

int MinHeap::findIndex(const intersection* ptr)
{
    for(int i = 0; i < heapSize; i++)
    {
        if(heapArray[i] == ptr)
        {
            return i;
        }
    }
    return -1;
}


void MinHeap::print()
{
    for(int i = 0; i < heapSize; i++)
    {
        heapArray[i]->print();
    }
}


void shortestDist(int start, int dest, MinHeap &mh)
{
    intersection * current = I[start];
    mh.insertKey(current);
    mh.decreaseKey(current, 0);
    while(current != I[dest])     //Need to find a good argument for while loop
    {
        for(int i = 0; i < current->R.size(); i++)
        {
            if(current == current->R[i]->a && (current->weight + current->R[i]->length) < current->R[i]->b->weight)
            {
                intersection* other = current->R[i]->b;
                other->weight = current->weight + current->R[i]->length;
                other->prev = current;
                mh.insertKey(other);
            }
            else if(current == current->R[i]->b && (current->weight + current->R[i]->length) < current->R[i]->a->weight)
            {
                intersection* other = current->R[i]->a;
                other->weight = current->weight + current->R[i]->length;
                other->prev = current;
                mh.insertKey(other);
            }
        }
        current->visited = true;
        cout << mh.extractMin()->name << " was visited." << endl;
        current = mh.getMin();
        cout << current->name << " is current location." << endl << endl;
        
        
        
    }
    current = I[dest];
    int length = 0;;
    while(current != I[start])
    {
        for(int i = 0; i < current->R.size(); i++)
        {
            if(current == current->R[i]->a && (current->weight - current->R[i]->length) == current->R[i]->b->weight)
            {
                length = length + current->R[i]->length;
                intersection* other = current->R[i]->b;
                cout << other->name << endl;
                current = other;
            }
            else if(current == current->R[i]->b && (current->weight - current->R[i]->length) == current->R[i]->a->weight)
            {
                length = length + current->R[i]->length;
                intersection* other = current->R[i]->a;
                cout << other->name << endl;
                current = other;
            }
        }
        
    }
    cout << "Length: " << (double)length/10000 << endl;
}

void prompt(DynamicHashTable &hashTable, vector<abb> &vec, MinHeap &mh)
{
    int index1;
    int index2;
    string input;
    string input_s;

    cout << "What city/town will you start at?" << endl;
    cout << "> ";
    getline(cin, input);
    if(input == "Q" || input == "q")
    {
        exit(0);
    }
    if(!hashTable.n_find(input, vec))
    {
        cout << endl;
        search(hashTable, vec);
    }
    cout << endl << "> ";
    getline(cin, input_s);
    if(input_s == "Q" || input_s == "q")
    {
        exit(0);
    }
    Location* loc1 = hashTable.s_find(input, input_s);

    
    index1 = findInter(loc1);

    cout << "What city/town will you end at?" << endl;
    cout << "> ";
    getline(cin, input);
    if(input == "Q" || input == "q")
    {
        exit(0);
    }
    if(!hashTable.n_find(input, vec))
    {
        cout << endl;
        search(hashTable, vec);
    }
    cout << endl << "> ";
    getline(cin, input_s);
    if(input_s == "Q" || input_s == "q")
    {
        exit(0);
    }
    Location* loc2 = hashTable.s_find(input, input_s);
    index2 = findInter(loc2);
    
    shortestDist(index1, index2, mh);
}


int main()
{
    DynamicHashTable hashTable;
    readInter("../Files/intersections.txt");
    readRoads("../Files/connections.txt");
    vector<abb> vec = load_states();
    ifstream fin;
    fin.open("../Files/named-places.txt");
    if (fin.fail()) {
        cout << "File could not be opened." << endl;
        exit(1);
    }
    
    string line;
    while (getline(fin, line))
    {
        hashTable.insert(Location(line));
    }
    fin.close();
    MinHeap mh(100);
    prompt(hashTable, vec, mh);
    
    return 0;
}
