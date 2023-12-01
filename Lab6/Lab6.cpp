#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Table(int row, int columns, vector<int> &V)
{
    // Allocate memory for the 2D array
    bool **table = new bool*[row];
    for(int i = 0; i < row; i++) {
        table[i] = new bool[columns+1];
        for(int j = 0; j < columns + 1; j++) {
            table[i][j] = false;
        }
    }

    // Populate the table
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < columns + 1; j++)
        {
            if(j == 0) {
                table[i][j] = true;
            }
            if(V[i] == j) {
                table[i][j] = true;
                if(i > 0)
                {
                    for(int k = i; k > 0; k--) {
                        int sum = V[i] + V[k-1];
                        if (sum < columns + 1) {
                            table[i][sum] = true;
                        }
                    }
                }
            }
            if((i > 0 && table[i-1][j] == true) || (i > 0 && j - V[i] >= 0 && table[i-1][j-V[i]]) == true) {
                table[i][j] = true;
            }
        }
    }
/*
    // Print the table for debugging
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < columns + 1; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
*/
    bool found = false;
    // Finding the closest answer
    for(int j = columns + 1; j >= 0; j--)
    {
        for(int i = 0; i < row; i++)
        {
            if( table[i][j] == true)
            {
                cout << j << endl;
                found = true;
                break;
            }
        }
        if(found == true)
        {
            break;
        }
    }
    
    // Deallocate memory
    for(int i = 0; i < row; i++) {
        delete[] table[i];
    }
    delete[] table;
}

int main()
{
    vector<int> V = {3631, 1567, 1543, 4499, 2514, 2548, 4051, 1190, 4365, 3727, 4392, 1745, 4466, 4626, 2161, 2354, 20000};

    int final = V.back();
    V.pop_back();
    
    cout << "\nVector size: " << V.size() << ", Last element: " << final << endl;

    Table((int)V.size(), final, V);

    return 0;
}

