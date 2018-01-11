/*
https://www.hackerrank.com/challenges/crush/problem
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<long long> arr(n + 1, 0);

    while (m--) {
        int a; int b; int k;
        cin >> a >> b >> k;
        arr[a-1] += k;
        arr[b] -= k;
    }

    long long max = 0;
    long long value = 0;
    for (auto const& item: arr) {
        value += item;
        if (value > max)
            max = value;
    }

    cout << max;
    return 0;
}
