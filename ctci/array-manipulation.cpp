/*
https://www.hackerrank.com/challenges/crush/problem
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int m;
    cin >> n >> m;

    vector<int> arr;
    for (size_t i=0; i<n; i++)
        arr.push_back(0);

    for(int a0 = 0; a0 < m; a0++){
        int a; int b; int k;
        cin >> a >> b >> k;
        
        for (size_t i=a-1; i<b-1; i++)
            arr[i] += k;
    }

    vector<int>::iterator found = max_element(arr.begin(), arr.end());
    cout << *found;

    return 0;
}
