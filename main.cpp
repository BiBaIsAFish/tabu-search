#include <bits/stdc++.h>
#include "TS.cpp"

using namespace std;

class testData {
public:
    int n;
    long long int w;
    vector<long long int> profits;
    vector<long long int> weights;
    string path;

    void readFile() {
        fstream f;
        f.open(path);
        if (!f.is_open()) {
            cout << "cannot open file." << endl;
            exit(1);
        }
        
        string line;
        getline(f, line);
        stringstream ss(line);
        ss >> n;
        profits.resize(n);
        weights.resize(n);
        int id;
        for (int loop = 0; loop < n; ++loop) {
            getline(f, line);
            ss = stringstream(line);
            ss >> id >> profits[loop] >> weights[loop];
        }
        getline(f, line);
        ss = stringstream(line);
        ss >> w;
        f.close();
    }

    void displayData() const {
        cout << "Number of items: " << n << endl;
        cout << "Knapsack capacity: " << w << endl;
        for (int i = 0; i < n; ++i) {
            cout << profits[i] << " " << weights[i] << endl;
        }
    }

    testData(string path) : path{path} {
        readFile();
    };
};

int main () {
    // testData td = testData("./testFile/test01.txt"); // 9999946233
    // testData td = testData("./testFile/test02.txt");
    testData td = testData("./testFile/test03.txt"); // 9999964987
    tabuSearch ts = tabuSearch(td.n, td.w, td.profits, td.weights);
    
    cout << "start solve. w = " << ts.w << ", n = " << ts.n << endl;
    auto result = ts.solve();
    cout << "max profit: " << result.second << endl;
    cout << "solution: " << result.first << endl;
}