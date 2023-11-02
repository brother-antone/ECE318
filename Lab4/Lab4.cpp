#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct intersection;
struct road;

vector <intersection*> I;

struct intersection
{
    double longi;
    double lati;
    float dist;
    string state;
    string name;

    vector<road*> R;
    
    intersection(double lo, double la, float d, string s, string n)
    {
        longi = lo;
        lati = la;
        dist = d;
        state = s;
        name = n;
    }

    void print()
    {
        cout << longi << " " << lati << " " << dist << " " << state << " " << name << endl;
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
        a->print()
        cout << "Intersection B: ";
        b->print();
        cout << length << endl;
        
    }
    
};

void readInter(const string &file_name)
{
    ifstream fin;
    fin.open(file_name);

    double lo;
    double la;
    float d;
    string s;
    string n;
    
    if(fin.fail())
    {
        cout << "Error opening " << file_name << endl;
        return;
    }

    while(!fin.eof())
    {
        fin >> lo >> la >> d >> s >> n;
        intersection * i = new intersection(lo, la, d, s, n);
        I.push_back(i);
    }
    
    fin.close();
    cout << file_name << "read successful" << endl;
}

//void readRoads

int main()
{
    
    
    return 0;
}
