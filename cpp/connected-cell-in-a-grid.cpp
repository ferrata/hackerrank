#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

typedef vector< vector<int> > graph_t;

int get_region( graph_t& graph, int i, int j ) {
    if ( i < 0 || j < 0 )
        return 0;
    if ( i >= graph.size() || j >= graph[i].size() )
        return 0;
    if ( graph[i][j] < 1 )
        return 0;
    auto value = graph[i][j];
    graph[i][j] = -1;
    for ( auto k = -1; k <= +1; k++ )
        for ( auto m = -1; m <= +1; m++ )
            if ( k || m )
                value += get_region( graph, i + k, j + m );
    return value;
    }

int get_biggest_region( graph_t& graph ) {
    int largest_region = 0;
    for ( int i = 0; i < graph.size(); i++ )
        for ( int j = 0; j < graph[i].size(); j++ )
            largest_region = max( largest_region, get_region( graph, i, j ) );
    return largest_region;
    }

int main() {
    int n;
    int m;
    cin >> n;
    cin >> m;
    graph_t graph( n, vector<int>(m) );
    for ( auto i = 0; i < n; i++ ) {
        for ( auto j = 0; j < m; j++ ) {
            cin >> graph[i][j];
            }
        }
    cout << get_biggest_region( graph ) << endl;
    return 0;
}
