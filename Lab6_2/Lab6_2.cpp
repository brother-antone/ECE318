#include <iostream>
#include <vector>

using namespace std;

int find(vector<int> &V, int final)
{
    int best = -1;
    for(int i = 0; i < (int)V.size(); i++)
    {
        for(int j = 1; j < (int)V.size(); i++)
        {
            int temp = V[i] + V[j];
            if(V[i] != V[j] && temp > best && temp <= final)
            {
                best = temp;
            }
        }
    }
    return best;
}

int main()
{
    vector<int> V = {14, 8, 11, 5, 14, 18, 4, 15, 11, 79};

    int final = V.back();
    V.pop_back();

    find(V, final);
}