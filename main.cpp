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

    void print(const vector<double>& v)
    {
        cout << "\n <";
        for(unsigned i =0; i<v.size(); i++)
           cout << v.at(i) << "\t";
        cout << ">\n";
    }
    void print(const vector<int>& v)
    {
        cout << "\n <";
        for(unsigned i =0; i<v.size(); i++)
           cout << v.at(i) << "\t";
        cout << ">\n";
    }

    double accuracy(vector<int>& currentSet, int feature_to_add)
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
                    vector<int> checkSet = currentSet; checkSet.push_back(feature_to_add);
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

    void searchFeatures()
    {
        vector<int> currentSet(1,0);
        int feature_to_add;
        double _accuracy = 0.00, best_so_far_accuracy = 0.00;
        for(unsigned i=1; i< data.at(0).size(); i++)
        {
            // cout << "On the " << i << "th level of the search tree\n";
            best_so_far_accuracy = 0.00;
            for(unsigned k = 1; k< data.at(0).size(); k++)
            {
                
                if(isPresent(currentSet, k))
                {
                    continue;
                }
                _accuracy = accuracy(currentSet, k);
                // cout << "------Consider adding the (" << k << ") feature with acc: " << _accuracy << "\n";
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
            // cout << "added feature (" << feature_to_add << ")\n"; 
            // cout << "--||--CurrentSet:[" << currentSet.at(1);
            // for(unsigned j=2; j<currentSet.size(); j++)
            // {
            //     cout << ", " << currentSet.at(j);
            // } cout << "] with accuracy " << best_so_far_accuracy << ".\n\n";
        }
        cout << "\n\n Therefore most accurate with accuracy of " << overall_best_accuracy;
        print(overall_most_Accurate);

    }
//added findAndDelete and backwardElimination
//recheck backwardElimination
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
    }


    void backwardElimination()
    {
        // vector<int> currentSet(data.at(0).size(), 0); 
        vector<int> currentSet(1,0);

        for(unsigned i =0; i<classLabel.size(); i++)
            currentSet.push_back(i+1);
        
        vector<int> checkSet = currentSet;
        int feature_to_delete;
        double _accuracy = 0.00, best_so_far_accuracy = 0.00;
        for(unsigned i = 1; i<data.at(0).size(); i++)
        {
            cout << "On the " << i << "th level of the search tree\n";
            best_so_far_accuracy = 0.00;
            for(unsigned k =1; k<currentSet.size(); k++)
            {
                if(!isPresent(currentSet, k))
                {
                    continue;
                }
                feature_to_delete = currentSet.at(k);
                findAndDelete(checkSet, k);
                _accuracy = accuracy(checkSet, k);
                if(_accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = _accuracy;
                    currentSet = checkSet;
                }
                cout << "Consider deleting feature " << k << "getting accuracy: " << _accuracy << "\n";
            }

            // currentSet = checkSet;
        }
        
    }
};



int main()
{
    /*
        On small dataset 50 the error rate can be 0.932,
        when using only features 6  5  1
    */

   /*
        On large dataset 66 the error rate can be 0.957,
        when using only features 1   3  22
   */

  /*(
    On small dataset 96(sue-small) the error rate can be 0.94,
     when using only features 1  3  6

    On large dataset 21(sue-large) the error rate can be 0.947,
     when using only features 37  36  40

    
  )*/

    string inputFile;
    cout << "Enter file name: ";
    cin >> inputFile;

    FeatureSelection* ob = new FeatureSelection();
    ob->readData(inputFile);
    // ob->printData();
    auto start = high_resolution_clock::now();
    ob->searchFeatures();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout << "Time taken: " << duration.count()/1000000.0 << " seconds\n";

    // cout << "Class Label size: " << ob->classLabel.size() << "\nData.size(): " << ob->data.size() << "\nObject.size(): " << ob->data.at(0).size() << endl;
    return 0;
}