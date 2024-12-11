#include <bits/stdc++.h>

using namespace std;

class tabuSearch {
public:
    // n, w, profits, weights
    tabuSearch(int n, long long int w, vector<long long int> &profits, vector<long long int> &weights)
    : n{n}, w{w}, profits{profits}, weights{weights} {} 

    pair<string, long long int> solve() {
        unordered_map<string, bool> tabuList;
        vector<int> finalSolution = getInitialSolution();
        long long int finalProfit = 0;
        
        vector<int> currentSolution = finalSolution;
        for (int loop = 0; loop < iteration; ++loop) {
            vector<vector<int>> neighbors = getNeighbors(currentSolution);
            long long int currentProfit = -1;

            for (const auto& neighbor : neighbors) {
                if (tabuList[toString(neighbor)]) {
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

            tabuList[toString(currentSolution)] = true;
            if (finalProfit < currentProfit) {
                finalProfit = currentProfit;
                finalSolution = currentSolution;
            }
        }

        return {toString(finalSolution), finalProfit};
    }

    void displayData() const {
        cout << "Number of items: " << n << endl;
        cout << "Knapsack capacity: " << w << endl;
        for (int i = 0; i < n; ++i) {
            cout << profits[i] << " " << weights[i] << endl;
        }
    }

    int n;
    long long int w;
    int tabuListSize = 2000;
    int iteration = 1000;
    vector<long long int> profits;
    vector<long long int> weights;

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
        for(int i : solution) {
            res += i ? "1" : "0";
        }

        return res;
    }
};