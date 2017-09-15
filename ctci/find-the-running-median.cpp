#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main(){
    int count;
    cin >> count;
    
    double median = 0;
    cout.precision( 1 );
    
    priority_queue<int, vector<int>, less<int> > left;
    priority_queue<int, vector<int>, greater<int> > right;
    
    for ( int i = 0; i < count; i++ ) {
        int v;
        cin >> v;

        if ( left.size() == right.size() )
            left.push( v );
        else 
            right.push( v );

        if ( right.size() && left.top() > right.top() ) {
            left.push( right.top() );
            right.push( left.top() );
            left.pop();
            right.pop();
            }

        if ( left.size() == right.size() )
            median = ( left.top() + right.top() ) * .5;
        else
            median = left.top();
            
        cout << fixed << median << endl;
        }
    return 0;
    }
