#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void readData()
{
    string inputFile;
    int numWhiteSpace;
    cout << "Enter file name: ";
    cin >> inputFile;
    string line;
    stringstream s;
    while(s.eof())
    {
        getline(line, s);

    }

    stringstream s(inputFile);

}




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

//figure out a way to store all columns in different vectors
/*
   2.0000000e+00  -1.6856194e+00  -8.2212726e-01  -9.8802171e-02  -1.4763174e+00   6.9730243e-01   4.9409603e-01
   2.0000000e+00   6.2396174e-01  -7.1416047e-01  -2.2071887e-01   5.3700084e-01   1.2121931e+00   8.1062900e-01
   2.0000000e+00  -5.0349633e-01   9.5791987e-02  -7.7479435e-01  -4.6605216e-01  -7.9045539e-02   1.0480600e+00
   2.0000000e+00   6.2674307e-01   1.0128217e+00   2.2176966e-01  -4.8848927e-01  -6.1323184e-01  -3.0474997e-01
   2.0000000e+00   3.2904579e-02  -4.7802459e-01  -1.7449811e+00   1.8932076e-01   1.1703449e+00  -1.0403758e+00
   1.0000000e+00   4.9505772e-01   1.3498230e+00   1.3792077e+00   1.9060491e+00   5.0093139e-01   3.2274267e-01
   2.0000000e+00  -2.6785130e-01  -8.5175656e-01   6.6862296e-01  -2.6299917e-01   8.8922018e-01  -2.0866763e+00
   2.0000000e+00  -1.5453729e+00   9.4183307e-01  -3.3008964e-01   8.9087028e-01  -1.0487057e+00   5.5630898e-01
   2.0000000e+00   2.6896249e-01   1.2929947e+00   1.6490864e+00  -5.2318139e-01   2.6381041e-01  -2.8480886e-01
   2.0000000e+00  -8.1467793e-01   4.8304905e-01   1.1513025e+00   1.9883022e+00   5.8264423e-01   7.4807420e-01

        0               1               2               3               4               5                  6 

    Create vector for objects for n rows.
        --> So basically data, is a vector of vectors... 
        -- Each object is a vector that stores its class label at index 0, and features at other indexes
    vector size = numSpaces + 1;
    vector.at(0) = class label
    vector.at(1,2,3...n) = features

*/