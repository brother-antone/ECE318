#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Table
{
private:
    int row;
    int columns;
    vector<int> V;
    bool **table;

public:
    Table(int r, int c, vector<int> &v) : row(r), columns(c), V(v)
    {
        table = new bool *[row];
        for(int i = 0; i < row; i++)
        {
            table[i] = new bool [columns + 1];
            for(int j = 0; j < columns + 1; j++)
            {
                table[i][j] = false;
            }
        }
        populateTable();
    }

    ~Table()
    {
        for(int i = 0; i < row; i++)
        {
            delete[] table[i];
        }
        delete[] table;
    }

    void populateTable()
    {
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < columns + 1; j++)
            {
                if (j == 0)
                {
                    table[i][j] = true;
                }
                if (V[i] == j)
                {
                    table[i][j] = true;
                }
                if ((i > 0 && table[i-1][j] == true) || (i > 0 && j - V[i] >= 0 && table[i-1][j - V[i]] == true))
                {
                    table[i][j] = true;
                }
            }
        }
    }

    void displayTable()
    {
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < columns + 1; j++)
            {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
    }

    int findClosestValue()
    {
        bool found = false;
        int answer = -1;

        for(int j = columns + 1; j >= 0; j--)
        {
            for(int i = 0; i < row; i++)
            {
                if(table[i][j] == true)
                {
                    answer = j;
                    found = true;
                    break;
                }
            }
            if(found)
            {
                break;
            }
        }
        return answer;
    }

    vector<int> findSteps(int answer)
    {
        vector <int> s;
        int j = answer;
        for(int i = row - 1; i >= 0; i--)
        {
            if(i == 0 && table[i][j] == true)
            {
                s.push_back(j);
                break;
            }
            if(table[i][j] == true && table[i-1][j] == false)
            {
                s.push_back(V[i]);
                j = j - V[i];
            }
            
        }
        return s;
    }
};

int main()
{
    vector<int> V = {3631, 1567, 1543, 4499, 2514, 2548, 4051, 1190, 4365, 3727, 4392, 1745, 4466, 4626, 2161, 2354, 20000};

    int final = V.back();
    V.pop_back();

    Table t((int)V.size(), final, V);

    int answer = t.findClosestValue();
    cout << "Best possible sum is: " << answer << endl;

    vector <int> Steps = t.findSteps(answer);
    
    for(int i = 0; i < (int)Steps.size(); i++)
    {
        cout << Steps[i] << endl;
    }
    
    return 0;
}
