/*
https://www.hackerrank.com/challenges/crush/problem
*/

#include <bits/stdc++.h>

using namespace std;

class ranges_t {
    typedef pair<int, int> range_t;
    typedef map<range_t, long long> ranges_map_t;

    ranges_map_t ranges_;

public:
    void add(int from, int to, int value) {
        auto item = ranges_.insert(make_pair(range_t(from, to), value));
        if (item.second == false)
            item.first->second += value;
    }

    long long find_max() {
        long long max = 0;
        long long current = 0;
        map<int, long long> window;

        for (const auto& it: ranges_) {
            auto range = it.first;
            auto range_value = it.second;
            
            auto remove_up_to = window.lower_bound(range.first);
            for (auto r = window.begin(); r != remove_up_to; r++)
                current -= r->second;
            window.erase(window.begin(), remove_up_to);

            auto item = window.insert(make_pair(range.second, range_value));
            if (item.second == false)
                item.first->second += range_value;
            current += range_value;

            if (current > max)
                max = current;
        }
        return max;
    }
};

int main() {
    int n;
    int m;
    cin >> n >> m;

    ranges_t ranges;
    for (int a0 = 0; a0 < m; a0++) {
        int a; int b; int k;
        cin >> a >> b >> k;
        ranges.add(a, b, k);
    }

    cout << ranges.find_max();
    return 0;
}
