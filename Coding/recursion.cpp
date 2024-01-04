#include<bits/stdc++.h>

using namespace std;

void printSubSequencesWithSumK(int index, vector<int> arr, int currSum, int k) {
    if(index == arr.size()) {
        if(currSum == k) {
            cout << "Exists\n";
        }
        return;
    }
    printSubSequencesWithSumK(index + 1, arr, currSum, k);
    printSubSequencesWithSumK(index + 1, arr, currSum + arr[index], k);
}

int houseRobber(vector<int> nums) {
    vector<int> dp(nums.size(), 0);
    for(int i = 0; i < nums.size(); i++) {
        if(i >= 2) {
            dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
        } else {
            dp[i] = nums[i];
        }
    }
    return dp[nums.size() - 1];
}

int ninjaTraining(vector<vector<int>> points) {
    vector<vector<int>> dp(points.size(), vector<int>(points[0].size(), 0));
    for(int i = 0; i < points[0].size(); i++) {
        dp[0][i] = points[0][i];
    }
    for(int i = 1; i < points.size(); i++) {
        for(int j = 0; j < points[0].size(); j++) {
            int ans = INT_MIN;
            for(int k = 0; k < points[0].size(); k++) {
                if(j == k) {
                    continue;
                }
                ans = max(ans, dp[i - 1][k]);
            }
            dp[i][j] = ans + points[i][j];
        }
    }
    int finalAns = 0;
    for(int i = 0; i < points[0].size(); i++) {
        finalAns = max(finalAns, dp[points.size() - 1][i]);
    }
    for(int i = 0; i < points.size(); i++) {
        for(int j = 0; j < points[0].size(); j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    return finalAns;
}

int main(int argc, char const *argv[]) {
    vector<vector<int>> points = {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90}
    };
    cout << "Ninja training = " << ninjaTraining(points) << "\n";
    return 0;
}
