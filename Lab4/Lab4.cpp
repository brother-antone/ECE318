#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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
