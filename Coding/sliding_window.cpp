#include<bits/stdc++.h>

using namespace std;

int maximumSubArrayWithSumK(vector<int> arr, int K) {
    unordered_map<int,int> prefixSumMap;
    int maxLen = 0;
    int sum = 0;
    for(int i = 0; i < arr.size(); i++) {
        sum = sum + arr[i];
        if(prefixSumMap.find(sum - K) != prefixSumMap.end()) {
            maxLen = max(maxLen, i - prefixSumMap[sum - K]);
        }
        if(prefixSumMap.find(sum) == prefixSumMap.end()) {
            prefixSumMap[sum] = i;
        }
    }
    return maxLen;
}

int longestSubStringWithKUniqueChars(string str, int K) {
    int maxLen = 0;
    map<char,int> charMap;
    int uniqueCharsCount = 0;
    int i = 0;
    int j = 0;
    int n = str.length();
    while(j < n) {
        charMap[str[j]]++;
        if(charMap[str[j]] == 1) {
            uniqueCharsCount++;
        }
        if(uniqueCharsCount < K) {
            j++;
        } else if(uniqueCharsCount == K) {
            maxLen = max(maxLen, j - i + 1);
            j++;
        } else {
            while(uniqueCharsCount > K) {
                charMap[str[i]]--;
                if(charMap[str[i]] == 0) {
                    uniqueCharsCount--;
                }
                i++;
            }
            j++;
        }
    }
    return maxLen;
}

string minimumWindowSubstring(string s, string t) {
    map<char,int> charMap;
    for(int i = 0; i < t.length(); i++) {
        charMap[t[i]]++;
    }
    int charsCount = charMap.size();
    int i = 0;
    int j = 0;
    int minLen = INT_MAX;
    string answer = "";
    while(j < s.length()) {
        if(charMap.find(s[j]) != charMap.end()) {
            charMap[s[j]]--;
            if(charMap[s[j]] == 0) {
                charsCount--;
            }
        }
        if(charsCount == 0) {
            while(charsCount == 0) {
                if(j - i + 1 < minLen) {
                    minLen = j - i + 1;
                    answer = s.substr(i, j - i + 1);
                }
                if(charMap.find(s[i]) != charMap.end()) {
                    charMap[s[i]]++;
                    if(charMap[s[i]] == 1) {
                        charsCount++;
                    }
                } 
                i++;
            }
            j++;
        } else {
            j++;
        }
    }
    return answer;
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    cout << "Length of minimum window substring in " << s <<" for " << t << " is " << minimumWindowSubstring(s, t) << "\n";
    return 0;
}