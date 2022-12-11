#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;
using namespace std::chrono;

class FeatureSelection
{
 public:
    vector<vector<double> > data;
    vector<double> row;
    vector<int> classLabel;
    double data_val;
    vector<int> overall_most_Accurate; double overall_best_accuracy = 0.0;


    void readData(const string& inputFile)
    {
        string line;
        ifstream inFS;
        inFS.open(inputFile);
        if(inFS.fail())
        { 
            cout << "Unable to open " << inputFile <<".\n"; 
            return; 
        } 
        while(!inFS.eof())
        {
            getline(inFS, line); line += "\n  ";
            stringstream ss(line); ss.clear(); ss.str(line);
            // cout << "Line: " << line << endl;
            ss >> data_val;
            classLabel.push_back(data_val);
            row.push_back(0.0);
            while(!ss.eof())
            {
                ss >> data_val;
                if(ss.eof())
                    continue;
                row.push_back(data_val);
            }
            data.push_back(row);
            row.clear();
        } 
        inFS.close();
        // for(unsigned i=0; i<classLabel.size(); i++)
        // {
        //     cout << i+1 << "): " << classLabel.at(i) << endl;
        // }
    }

    void printData()
    {
        cout << "\n-----------------------------------------------------------------------------------------\n";
        for(unsigned i  = 0; i<data.size(); i++)
        {{
            for(unsigned j=0; j<data.at(i).size(); j++)
                cout << fixed << setprecision(8) << data.at(i).at(j) << "\t";
        }cout << endl;}
        cout << "-----------------------------------------------------------------------------------------\n";
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

    void printSet(const vector<int>& v)
    {
        cout << "\n[" << v.at(1);
        for(unsigned i =2; i<v.size(); i++)
           cout << ", " << v.at(i);
        cout << "]\n";
    }

    double accuracy(vector<int>& currentSet, int feature_number, const string& searchType)
    {
        double distance = 0.000;
        double nn_distance = 99999999.99999999;
        int nn_pos = 9999999;
        int nn_label = 0;
        double _accuracy = 0.000;

        for(unsigned i=0; i<data.size(); i++)
        {
            nn_distance = 99999999.99999999;
            for(unsigned k=0; k<data.size(); k++)
            {
                distance = 0.000;
                if(k!=i)
                {
                    vector<int> checkSet = currentSet; 
                    if(searchType == "forward")
                        checkSet.push_back(feature_number);
                    else if(searchType == "backward")
                        findAndDelete(checkSet, feature_number);
                    int m = checkSet.at(0);
                    for(unsigned j =1; j<checkSet.size(); j++)
                    {
                        m = checkSet.at(j);
                        distance += pow((data.at(i).at(m) - data.at(k).at(m)),2);
                    }
                    distance = sqrt(distance);
                    if(distance < nn_distance)
                    {
                        nn_distance = distance;
                        nn_pos = k;
                        nn_label = classLabel.at(k);
                    }
                }
            }
                        
            if(nn_label == classLabel.at(i))
            {
                _accuracy++;
            }
        }
        
        _accuracy /= static_cast<double>(data.size());
        return _accuracy;

    }

    void forwardSelection()
    {
        vector<int> currentSet(1,0);
        int feature_to_add;
        double _accuracy = 0.00, best_so_far_accuracy = 0.00;
        for(unsigned i=1; i< data.at(0).size(); i++)
        {
            cout << "On the " << i << "th level of the search tree\n";
            best_so_far_accuracy = 0.00;
            for(unsigned k = 1; k< data.at(0).size(); k++)
            {
                
                if(isPresent(currentSet, k))
                {
                    continue;
                }
                _accuracy = accuracy(currentSet, k, "forward");
                cout << "------Consider adding the (" << k << ") feature with acc: " << _accuracy << "\n";
                if(_accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = _accuracy;
                    feature_to_add = k;
                }
            }
            currentSet.push_back(feature_to_add);
            if(best_so_far_accuracy > overall_best_accuracy) 
            {
                overall_most_Accurate = currentSet;
                overall_best_accuracy = best_so_far_accuracy;
            }
            cout << "added feature (" << feature_to_add << ")\n"; 
            cout << "--||--CurrentSet:[" << currentSet.at(1);
            for(unsigned j=2; j<currentSet.size(); j++)
            {
                cout << ", " << currentSet.at(j);
            } cout << "] with accuracy " << best_so_far_accuracy << ".\n\n";
        }

    }

    void findAndDelete(vector<int>& v, int x)
    {
        unsigned int i;
        for(i=0; i<v.size(); i++)
        {
            if(v.at(i)==x)
                break;
        }
        v.at(i) = v.at(v.size()-1);
        v.pop_back();
        sort(v.begin(), v.end());
    }

    void backwardElimination()
    {
        vector<int> currentSet(1,0);
        for(unsigned i =1; i<data.at(0).size(); i++)
            currentSet.push_back(i);
        
        vector<int> checkSet = currentSet; int feature_to_delete;
        double _accuracy = 0.00, best_so_far_accuracy = 0.00;
        
        int i = 1;
        while(currentSet.size()>1)
        {
            best_so_far_accuracy = 0.00;
            cout << "On the " << i << "th level of the search tree\n";
            for(unsigned k = 1; k<currentSet.size(); k++)
            {
                if(!isPresent(currentSet, currentSet.at(k)))
                {
                    continue;
                }
                _accuracy = accuracy(currentSet, currentSet.at(k), "backward");
                cout << "------Consider deleting feature(" << currentSet.at(k) << "),which gives accuracy: " << _accuracy << "\n";
                if(_accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = _accuracy;
                    feature_to_delete = currentSet.at(k);
                }
            }
            findAndDelete(currentSet,feature_to_delete);

            if(best_so_far_accuracy > overall_best_accuracy) 
            {
                overall_most_Accurate = currentSet;
                overall_best_accuracy = best_so_far_accuracy;
            }

            cout << "Deleted feature (" << feature_to_delete << ")\n"; 
            cout << "--||--CurrentSet:[" << currentSet.at(0);
            for(unsigned j=1; j<currentSet.size(); j++)
            {
                cout << ", " << currentSet.at(j);
            } cout << "] with accuracy " << best_so_far_accuracy << ".\n\n";
            i++;
        }
    }
};



int main()
{

    string inputFile; int choice;
    cout << "Enter file name: ";
    cin >> inputFile;

    FeatureSelection* ob = new FeatureSelection();
    ob->readData(inputFile);
    // ob->printData();
    cout << "Choose one of the following choices. Enter either '1' or '2' only\n1. Forward Selection\t2. Backward Elimination\n";
    cin >> choice;
    
    auto start = high_resolution_clock::now();
    if(choice == 1)
        ob->forwardSelection();
    else if(choice == 2)
        ob->backwardElimination();
    else
    {
        cout << "Invalid choice\n";
        return 1;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    
    cout << "\n\n The best set of features for the provided dataset is:";
    ob->printSet(ob->overall_most_Accurate);
    cout << ", with an accuracy of " << ob->overall_best_accuracy;

    cout << "\n\n--<<Time taken: " << duration.count()/1000000.0 << " seconds>>--\n";

    return 0;
}