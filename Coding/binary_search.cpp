#include<bits/stdc++.h>

using namespace std;


 bool isPossible(int A[], int N, int maxPages, int M) {
        int studentsCount = 1;
        int pagesCount = 0;
        for(int i = 0; i < N; i++) {
            pagesCount += A[i];
            if(pagesCount > maxPages) {
                studentsCount++;
                pagesCount = A[i];
            }
        }
        return studentsCount <= M;
    }
    //Function to find minimum number of pages.
    int findPages(int A[], int N, int M) 
    {
        //code here
        int left = 1;
        int right = 0;
        int ans = -1;
        for(int i = 0; i < N; i++) {
            left = max(left, A[i]);
            right += A[i];
        }
        while(left <= right) {
            int mid = left + (right - left) / 2;
            cout << left << " " << mid << " " << right << "\n";
            if(isPossible(A, N, mid, M)) {
                ans = mid;
                right = mid - 1;
                cout << mid << "\n";
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

int main() {
    int A[] = {15, 10, 19, 10, 5, 18, 7};
    int N = 7;
    int M = 5;
    cout << "ANS = " << findPages(A, N, M) << "\n";
    return 0;
}