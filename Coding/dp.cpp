#include<bits/stdc++.h>

using namespace std;

int recursiveKnaspack(vector<int> weights, vector<int> values, int knapsackWeight, int n) {
    if(knapsackWeight == 0 || n == 0) {
        return 0;
    }
    if (weights[n-1] <= knapsackWeight) {
        return max(
            values[n-1] + recursiveKnaspack(weights, values, knapsackWeight - weights[n-1], n-1),
            recursiveKnaspack(weights, values, knapsackWeight, n-1)
        );
    } else {
        return recursiveKnaspack(weights, values, knapsackWeight, n-1);
    }
}

int memoizedKnapsack(vector<vector<int>> memoizedTable, vector<int> weights, vector<int> values, int knapsackWeight, int n) {
    if(n == 0 || knapsackWeight == 0) {
        return 0;
    }
    if(memoizedTable[n][knapsackWeight] != -1) {
        return memoizedTable[n][knapsackWeight];
    }
    if(weights[n-1] <= knapsackWeight) {
        return memoizedTable[n][knapsackWeight] =  max(
            values[n-1] + memoizedKnapsack(memoizedTable, weights, values, knapsackWeight - weights[n-1], n-1),
            memoizedKnapsack(memoizedTable, weights, values, knapsackWeight, n-1)
        );
    } else {
        return memoizedTable[n][knapsackWeight] = memoizedKnapsack(memoizedTable, weights, values, knapsackWeight, n-1);
    }
}

int topDownKnapsack(vector<int> weights, vector<int> values, int knapsackWeight, int n) {
    vector<vector<int>> dp(n+1, vector<int>(knapsackWeight+1, 0));
    for(int i=1; i <= n; i++) {
        for(int j=1; j <= knapsackWeight; j++) {
            if(weights[i-1] <= j) {
                dp[i][j] = max(values[i-1] + dp[i-1][j - weights[i-1]], dp[i-1][j]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][knapsackWeight];
}

int rodCuttingRecursive(int index, int length, vector<int> prices) {
    if(length == 0) {
        return 0;
    }
    if(index == 0) {
        return prices[index] * length;
    }
    int notCut = rodCuttingRecursive(index-1, length, prices);
    int cut = 0;
    if(length >= index + 1) {
        cut = prices[index] + rodCuttingRecursive(index, length - (index+1), prices);
    }
    cout << "Index = " << index << "Length = " << length << " NotCut = " << notCut << " Cut = " << cut << "\n";
    return max(cut, notCut);
}

int rodCutting(vector<int> prices, int n) {
    return rodCuttingRecursive(n-1, n, prices);
}

string ShortestCommonSuperSequence(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(str1[i-1] == str2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    string answer = "";
    int i = m;
    int j = n;
    while(i > 0 && j > 0) {
        if(str1[i-1] == str2[j-1]) {
            answer += str1[i-1];
            i--;
            j--;
        } else if(dp[i-1][j] > dp[i][j-1]) {
            answer += str1[i-1];
            i--;
        } else {
            answer += str2[j-1];
            j--;
        }
    }
    while(i > 0) {
        answer += str1[i-1];
        i--;
    }
    while(j > 0) {
        answer += str2[j-1];
        j--;
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

int LIS(vector<int> arr, int n, int index, int prev_index, vector<vector<int>> &dp) {
    if(index == n) {
        return 0;
    }
    if(dp[index][prev_index + 1] != -1) {
        return dp[index][prev_index + 1];
    }
    int notTake = LIS(arr, n, index+1, prev_index, dp);
    int take = 0;
    if(prev_index == -1 || arr[index] > arr[prev_index]) {
        take = 1 + LIS(arr, n, index+1, index, dp);
    }
    return dp[index][prev_index + 1] = max(take, notTake);
}

int mcmRecursive(vector<int> arr, int i, int j) {
    if(i == j) {
        return 0;
    }
    int ans = INT_MAX;
    for(int k = i; k <= j-1; k++) {
        int leftPartition = mcmRecursive(arr, i, k);
        int rightPartition = mcmRecursive(arr, k+1, j);
        int cost = arr[i-1] * arr[k] * arr[j];
        ans = min(ans, cost + leftPartition + rightPartition);
    }
    return ans;
}

int mcmTabulation(vector<int> arr, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = n-1; i >= 1; i--) {
        for(int j = i+1; j <= n-1; j++) {
            int ans = INT_MAX;
            for(int k = i; k <= j-1; k++) {
                int leftPartition = dp[i][k];
                int rightPartition = dp[k+1][j];
                int cost = arr[i-1] * arr[k] * arr[j];
                ans = min(ans, cost + leftPartition + rightPartition);
            }
            dp[i][j] = ans;
        }
    }
    return dp[1][n-1];
}

int f(int i, int j, vector<int> temp, int n) {
        if(i > j) {
            return 0; 
        }
        int minCost = INT_MAX;
        for(int k = i; k <= j; k++) {
            int currCost = temp[j+1] - temp[i-1];
            int leftCost = f(i, k-1, temp, n);
            int rightCost = f(k+1, j, temp, n);
            minCost = min(minCost, currCost + leftCost + rightCost);
        }
        return minCost;
}
int minCost(int n, vector<int>& cuts) {
        vector<int> temp;
        temp.push_back(0);
        for(int c : cuts) {
            temp.push_back(c);
        }
        temp.push_back(n);
        vector<vector<int>> dp(cuts.size() + 2, vector<int>(cuts.size() + 2, 0));
        for(int i = cuts.size(); i >= 1; i--) {
            for(int j = i; j <= cuts.size(); j++) {
                int minCost = INT_MAX;
                for(int k = i; k <= j; k++) {
                    int currCost = temp[j+1] - temp[i-1];
                    int leftCost = dp[i][k-1];
                    int rightCost = dp[k+1][j];
                    minCost = min(minCost, currCost + leftCost + rightCost);
                }
                dp[i][j] = minCost;
            }
        }
        for(int i = 0; i < dp.size(); i++) {
            for(int j = 0; j < dp[0].size(); j++) {
                cout << dp[i][j] << " ";
            }
            cout << "\n";
        }
        return dp[1][cuts.size()];
        // return f(1, cuts.size(), temp, n);
}

int booleanEvaluation(string str, int i, int j, bool isTrue) {
    if(i > j) {
        return 0;
    }
    if(i == j) {
        if(isTrue and str[i] == 'T') {
            return 1;
        } else if(!isTrue and str[i] == 'F') {
            return 1;
        } else {
            return 0;
        }
    }
    int ways = 0;
    for(int k = i + 1; k <= j - 1; k = k + 2) {
        int leftTrueWays = booleanEvaluation(str, i, k - 1, true);
        int leftFalseWays = booleanEvaluation(str, i, k - 1, false);
        int rightTrueWays = booleanEvaluation(str, k + 1, j, true);
        int rightFalseWays = booleanEvaluation(str, k + 1, j, false);
        if(isTrue) {
            if(str[k] == '&') {
                ways = ways + (leftTrueWays * rightTrueWays);
            } else if(str[k] == '|') {
                ways = ways + (leftTrueWays * rightTrueWays) + 
                (leftFalseWays * rightTrueWays) + (leftTrueWays * rightFalseWays);
            } else if(str[k] == '^') {
                ways = ways + (leftTrueWays * rightFalseWays) + (leftFalseWays * rightTrueWays);
            }
        } else {
            if(str[k] == '&') {
                ways = ways + (leftFalseWays * rightFalseWays) + 
                (leftTrueWays * rightFalseWays) + (leftFalseWays * rightTrueWays);
            } else if(str[k] == '|') {
                ways = ways + (leftFalseWays * rightFalseWays);
            } else if(str[k] == '^') {
                ways = ways + (leftTrueWays * rightTrueWays) + (leftFalseWays * rightFalseWays);
            }
        }
        // cout << "k = " << k << " ways = " << ways << "\n";
    }
    return ways;
}

int main(int argc, char const *argv[]) {
    // Knapsack Problem
    // int n = 3;
    // vector<int> weights{4, 5, 1};
    // vector<int> values{1, 2, 3    // int knapsackWeight = 4;
    // cout << "Maximum knapsack value : " << recursiveKnaspack(weights, values, knapsackWeight, n) << "\n";
    // vector<vector<int>> memoizedTable(n+1, vector<int>(knapsackWeight+1, -1));
    // cout << "Maximum knapsack value (memoized) : " << memoizedKnapsack(memoizedTable, weights, values, knapsackWeight, n) << "\n";
    // cout << "Maximum knapsack value (topdown) : " << topDownKnapsack(weights, values, knapsackWeight, n) << "\n";

    // // Rod Cutting Problem
    // vector<int> prices = {3, 5, 8, 9, 10, 17, 17, 20};
    // cout << "Maximum price of rods : " << rodCutting(prices, prices.size()) << "\n";

    // // Shortest Common SuperSequence
    // string s1 = "abac";
    // string s2 = "cab";
    // cout << "ShortestCommonSuperSequence = " << ShortestCommonSuperSequence(s1, s2) << "\n";

    // // Longest Increasing Subsequence
    // vector<int> arr = {10,9,2,5,3,7,101,18};
    // int n = arr.size();
    // vector<vector<int>> dp(n+1, vector<int>(n, -1));
    // cout << "Longest Increasing Subsequence : " << LIS(arr, arr.size(), 0, -1, dp) << "\n";

    // // Matrix Chain Multiplication
    // vector<int> arr = {40, 20, 30, 10, 30};
    // int n = arr.size();
    // cout << "MCM = " << mcmTabulation(arr, n) << "\n"; 

    // // Minimum Cost to cut sticks
    // vector<int> arr = {1,3,4,5};
    // int n = 7;
    // cout << "Minimum Cost to cut sticks = " << minCost(n, arr) << "\n";

    // Boolean Parenthesization
    string str = "T|T&F^T";
    int n = str.length();
    cout << "Boolean Parenthesization ways = " << booleanEvaluation(str, 0, n - 1, true) << "\n";

    return 0;
}
