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

    while(!fin1.eof())
    {
        fin1 >> lo >> la >> d >> s >> n;
        intersection * i = new intersection(lo, la, d, s, n);
        I.push_back(i);
    }
    
    fin1.close();
    cout << file1 << "read successful" << endl;
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

    while(!fin2.eof())
    {
        fin2 >> n >> t >> a >> b >> l;
        road * r = new road(n , t, I[a], I[b], l);
        I[a]->R.push_back(r);
    }
}

int main()
{
    
    
    return 0;
}
