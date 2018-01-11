#include <functional>
#include <set>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <iostream>

using namespace std;

typedef vector< vector<int> > graph_data_t;
class graph_t;

class node_t {
friend class graph_t;

private:
    int _i;
    int _j;
    bool _filled;
    
public:
    node_t( int i, int j, bool filled )
        : _i( i ), _j( j ), _filled( filled )
        {}

    bool is_filled() const { return _filled; }

    friend bool operator< ( const node_t& n1, const node_t& n2 );
    friend bool operator== ( const node_t& n1, const node_t& n2 );
    friend bool operator!= ( const node_t& n1, const node_t& n2 );
    // friend ostream& operator<< ( ostream& os, const node_t& n );
    };

bool operator< ( const node_t& n1, const node_t& n2 ) {
    if ( n1._i < n2._i )
        return true;
    if ( n1._i == n2._i && n1._j < n2._j )
        return true;
    return false;
    }
    
bool operator== ( const node_t& n1, const node_t& n2 ) {
    return n1._i == n2._i && n1._j == n2._j;
    }

bool operator!= ( const node_t& n1, const node_t& n2 ) {
    return !( n1 == n2 );
    }

// ostream& operator<< ( ostream& os, const node_t& n ) {  
//     return os << n._i << ':' << n._j << (n._filled ? " filled" : "");
//     }  
    
class graph_t {
private:
    graph_data_t _data;
    node_t _end;

    node_t find( int i, int j ) {
        if ( i >= 0 && i < _data.size() ) {
            auto row = _data.at( i );
            if ( j >=0 && j < row.size() ) {
                auto value = row.at( j );
                return node_t( i, j, value );
                }
            }
        return _end;
        }

    void append_found( vector<node_t>& r, int i, int j ) {
        auto n = find( i, j );
        if ( n != _end )
            r.push_back( n );
        }

public:
    graph_t( graph_data_t data ) : _data( data ), _end( -1, -1, false ) {}

    node_t root() {
        return node_t( 0, 0, _data[0][0] );
        }

    vector<node_t> children( const node_t& node ) {
        vector<node_t> r;
        // [i-1][j-1]   [i-1][j]   [i-1][j+1]
        // [i][j-1]        -       [i][j+1]
        // [i+1][j-1]   [i+1][j]   [i+1][j+1]
        auto i = node._i;
        auto j = node._j;
        append_found( r, i-1, j-1 );
        append_found( r, i-1, j );
        append_found( r, i-1, j+1 );
        append_found( r, i, j-1 );
        append_found( r, i, j+1 );
        append_found( r, i+1, j-1 );
        append_found( r, i+1, j );
        append_found( r, i+1, j+1 );
        return r;
        }
    };

int get_biggest_region( graph_t& graph ) {
    set<node_t> visited;
    deque<node_t> nodes;
    nodes.push_front( graph.root() );

    priority_queue<int, vector<int>, less<int> > found_regions;
    int current_region = 0;

    while ( nodes.size() ) {
        auto node = nodes.front();
        nodes.pop_front();
        
        if ( visited.find( node ) != visited.end() )
            continue;
        visited.insert( node );

        for ( auto child: graph.children( node ) ) {
            if ( child.is_filled() )
                nodes.push_front( child );
            else
                nodes.push_back( child );
            }
        
        if ( node.is_filled() )
            current_region += 1;
        else if ( current_region ) {
            found_regions.push( current_region );
            current_region = 0;
            }
        }

    if ( current_region )
        found_regions.push( current_region );
    return found_regions.size() ? found_regions.top() : 0;
    }

int main() {
    int n;
    int m;
    cin >> n;
    cin >> m;
    graph_data_t grid( n, vector<int>(m) );
    for( int grid_i = 0; grid_i < n; grid_i++ ) {
        for( int grid_j = 0; grid_j < m; grid_j++ ) {
            cin >> grid[grid_i][grid_j];
            }
        }
    graph_t g( grid );
    cout << get_biggest_region( g ) << endl;
    return 0;
    }
