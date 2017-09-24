#include <functional>
#include <vector>
#include <queue>
#include <iostream>

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
