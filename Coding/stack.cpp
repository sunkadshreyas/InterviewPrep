#include<bits/stdc++.h>

using namespace std;


vector<int> NSL(vector<int> nums) {
     vector<int> ans;
     stack<int> st;
     for(int i = 0; i < nums.size(); i++) {
         while(!st.empty() && nums[st.top()] > nums[i]) {
             st.pop();
         }
         if(st.empty()) {
             ans.push_back(-1);
         } else {
             ans.push_back(st.top());
         }
         st.push(i);
     }
     return ans;
 }
 vector<int> NSR(vector<int> nums) {
     vector<int> ans;
     stack<int> st;
     for(int i = nums.size() - 1; i >= 0; i--) {
         while(!st.empty() && nums[st.top()] > nums[i]) {
             st.pop();
         }
         if(st.empty()) {
             ans.push_back(nums.size());
         } else {
             ans.push_back(st.top());
         }
         st.push(i);
     }
     reverse(ans.begin(), ans.end());
     return ans;
 }
 int largestRectangleArea(vector<int>& heights) {
     vector<int> nsr = NSR(heights);
     vector<int> nsl = NSL(heights);
     for(int i = 0; i < heights.size(); i++) {
         cout << nsr[i] << " " << heights[i] << " " << nsl[i] << "\n";
     }
     int ans = 0;
     for(int i = 0; i < heights.size(); i++) {
         ans = max(ans, heights[i]);
         ans = max(ans, (nsr[i] - nsl[i] - 1) * heights[i]);
     }
     return ans;
 }

 vector<int> leftMax(vector<int> arr) {
     vector<int> maxInLeft(arr.size(), 0);
     int maxEleLeft = arr[0];
     for(int i = 1; i < arr.size(); i++) {
         maxInLeft[i] = maxEleLeft;
         if (arr[i] > maxEleLeft) {
             maxEleLeft = arr[i];
         }
     }
     return maxInLeft;
 }

 vector<int> rightMax(vector<int> arr) {
     vector<int> maxInRight(arr.size(), 0);
     int maxEleRight = arr[arr.size() - 1];
     for(int i = arr.size() - 2; i >= 0; i--) {
         maxInRight[i] = maxEleRight;
         if(arr[i] > maxEleRight) {
             maxEleRight = arr[i];
         }
     }
     return maxInRight;
 }

 int main(int argc, char const *argv[]) {
     vector<int> heights = {4,2,0,3,2,5};
     vector<int> maxInLeft = leftMax(heights);
     vector<int> maxInRight = rightMax(heights);
     int ans = 0;
     for(int i = 0; i < heights.size(); i++) {
         ans = ans + max((min(maxInLeft[i], maxInRight[i]) - heights[i]), 0);
     }
     cout << "Total rainwater trapped is : " << ans << "\n";
     return 0;
 }
