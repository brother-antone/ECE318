#include "hashtable.h"


using namespace std;



int main()
{

    HashTable ht("read");

    string input;
    string city;
    
    while(true)
    {
        cout << "> ";
        cin >> input;
        if(input == "N" || input == "n")
        {
            cin.ignore();
            cout << "Enter name" << endl << "> ";
            cin >> city;
            ht.n_find(city);
        }
        else if(input == "S" || input == "s")
        {
            continue;
        }
        else if(input == "Q" || input == "q")
        {
            break;
        }
    }
    return 0;
}