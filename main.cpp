#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

bool isPresent(vector<int>& v, int val)
{
    for(unsigned i=0; i<v.size(); i++)
    {
        if(v.at(i) == val)
            return true;
    }
    return false;
}

int accuracy(vector<int>& data, vector<int>& currentSet, int feature_to_add)
{

    // Testing if correct features are added in order
    // if(currentSet.size()==1)
    // {
    //     if(currentSet.at(0) == 1)
    //         return 62;
    //     else if(currentSet.at(0)==2)
    //         return 61;
    //     else if(currentSet.at(0)==3)
    //         return 51;
    //     else if(currentSet.at(0)==4)
    //         return 52;
    // }
    // else if(currentSet.size() == 2)
    // {
    //     int a = currentSet.at(0);
    //     int b = currentSet.at(1);
    //     if(a == 1)
    //     {
    //         if(b==2)
    //             return 97;
    //         else if(b==3)
    //             return 60;
    //         else if(b==4)
    //             return 58;
    //     }
    //     else if(a==2)
    //     {
    //         if(b==1)
    //             return 97;
    //         else if(b==3)
    //             return 1;
    //         else if(b==4)
    //             return 1;
    //     }
    //     else
    //         return 1;
    // }
    // else if(currentSet.size()==3)
    // {
    //     int a = currentSet.at(0);
    //     int b = currentSet.at(1);
    //     int c = currentSet.at(2);
    //     if(a==1)
    //     {
    //         if(b==2)
    //         {
    //             if(c==3)
    //                 return 87;
    //             else if(c==4)
    //                 return 88;
    //             else 
    //                 return 1;
    //         }
    //         else
    //             return 1;
    //     }
    //     else
    //         return 1;
    // }
    return (rand()%4 +1)*10;
}

void searchFeatures(vector<int>& data, int numCols)
{
    vector<int> currentSet(data.size()-1, 0); 
    int _accuracy, best_so_far_accuracy, feature_to_add;
    for(unsigned i=1; i< numCols; i++)
    {
        cout << "On the " << i << "th level of the search tree ";
        best_so_far_accuracy = 0;
        for(unsigned k = 1; k< numCols; k++)
        {
            if(isPresent(currentSet, k))
            {
                // cout << "\n--ALready present--\n";
                continue;
            }
            // cout << "   Consider adding the (" << k << ") feature\n";
            _accuracy = accuracy(data, currentSet, k+1);

            if(_accuracy >= best_so_far_accuracy)
            {
                best_so_far_accuracy = _accuracy;
                feature_to_add = k;
            }
        }
        currentSet.at(i-1) = feature_to_add;
        cout << "added feature (" << feature_to_add << ").\n\tCurrentSet:[" << currentSet.at(0);
        for(unsigned j=1; j<currentSet.size(); j++)
        {
            cout << ", " << currentSet.at(j);
        }
        cout << "]\n";
    }
}

int main()
{

    vector<int> data;
    for(unsigned i =0; i<=4; i++)
    {
        data.push_back(i);
    }
    cout << "Size of data: " << data.size() << "\n";
    searchFeatures(data, data.size());
    return 0;
}