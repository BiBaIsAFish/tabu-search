#include <bits/stdc++.h>

using namespace std;

class tabuSearch {
public:
    tabuSearch(int n, long long int w, vector<int> profits, vector<int> weights)
    : n{n}, w{w}, profits{profits}, weights{weights} {}

    pair<string, long long int> solve() {
        deque<vector<int>> tabuList;
        vector<int> finalSolution = getInitialSolution();
        long long int finalProfit = 0;
        
        vector<int> currentSolution = finalSolution;
        for (int loop = 0; loop < iteration; ++loop) {
            vector<vector<int>> neighbors = getNeighbors(currentSolution);
            long long int currentProfit = 0;

            for (const auto& neighbor : neighbors) {
                if (find(tabuList.begin(), tabuList.end(), neighbor) != tabuList.end()) {
                    continue;
                }

                long long int weight = 0, profit = 0;
                for (int i = 0; i < n; ++i) {
                    if (neighbor[i]) {
                        weight += weights[i];
                        profit += profits[i];
                    }
                }
                if (weight > w) {
                    continue;
                }
                if (profit > currentProfit) {
                    currentProfit = profit;
                    currentSolution = neighbor;
                }
            }

            tabuList.push_back(currentSolution);
            if (finalProfit < currentProfit) {
                finalProfit = currentProfit;
                finalSolution = currentSolution;
            }
        }

        return {toString(finalSolution), finalProfit};
    }
private:
    int n;
    long long int w;
    int tabuListSize = 2000;
    int iteration = 1000;
    vector<int> profits;
    vector<int> weights;

    vector<int> getInitialSolution() {
        srand(time(NULL));
        vector<int> solution(n, 0);
        
        for (int loop = 0; loop < 100; ++loop) {
            vector<int> currentSolution(n);
            for (int i = 0; i < n; ++i) {
                solution[i] = (rand() & 1);
            }

            long long int weight = 0;
            for (int i = 0; i < n; ++i) {
                weight += (currentSolution[i]) ? weights[i] : 0;
            }
            if (weight < w) {
                solution = currentSolution;
                break;
            }
        }

        return solution;
    }

    vector<vector<int>> getNeighbors(const vector<int>& sol) {
        vector<vector<int>> neighbors;
        for (int i = 0; i < n; ++i) {
            vector<int> curr = sol;
            curr[i] = 1 - sol[i];
            neighbors.push_back(curr);
        }

        return neighbors;
    }

    string toString(const vector<int>& solution) {
        string res = "";
        for (int i = 0; i < n; ++i) {
            res += (solution[i])? "1" : "0";
        }

        return res;
    }
};

void test1() {
    int n = 3, w = 4;
    vector<int> profits{1, 2, 3};
    vector<int> weights{4, 5, 1};

    tabuSearch ts = tabuSearch(n, w, profits, weights);
    auto result = ts.solve();
    cout << "max profit: " << result.second << endl;
    cout << "solution: " << result.first << endl;
}

void test2() {
    int n = 3, w = 3;
    vector<int> profits{1, 2, 3};
    vector<int> weights{4, 5, 6};

    tabuSearch ts = tabuSearch(n, w, profits, weights);
    auto result = ts.solve();
    cout << "max profit: " << result.second << endl;
    cout << "solution: " << result.first << endl;
}

void test3() {
    int n = 10, w = 165;
    vector<int> profits{92,57,49,68,60,43,67,84,87,72};
    vector<int> weights{23,31,29,44,53,38,63,85,89,82};

    tabuSearch ts = tabuSearch(n, w, profits, weights);
    auto result = ts.solve();
    cout << "max profit: " << result.second << endl;
    cout << "solution: " << result.first << endl;
}

int main () {
    // long long int w;
    // int n, currentWeight, currentProfit;
    // cout << "enter number and weight: " << endl;
    // cin >> n >> w;
    // cout << "enter weight[i] and profit[i]" << endl;
    // vector<int> profits(n), weights(n);

    // for (int i = 0; i < n; ++i) {
    //     cin >> currentWeight >> currentProfit;
    //     weights[i] = currentWeight, profits[i] = currentProfit;
    // }

    // tabuSearch ts = tabuSearch(n, w, profits, weights);
    // auto result = ts.solve();
    // cout << "max profit: " << result.second << endl;
    // cout << "solution: " << result.first << endl;

    test1();
    test2();
    test3();
}