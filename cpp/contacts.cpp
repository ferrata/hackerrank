#include <map>
#include <vector>
#include <iostream>

using namespace std;

class storage {
private:
    typedef map<string, vector<string>> digrams_t;
    typedef map<string, digrams_t> unigrams_t;
    
    unigrams_t _items;

    string make_unigram( string& item ) const {
        return item.substr( 0, 1 );
        }

    string make_digram( string& item ) const {
        string key = item.substr( 0, 2 );
        if ( key.length() < 2 )
            key.push_back( ' ' );
        return key;
        }
        
public:
    storage() : _items() {}

    void add( string& item ) {
        string unigram = make_unigram( item );
        unigrams_t::iterator digrams = _items.find( unigram );
        if ( digrams == _items.end() ) {
            _items.insert( make_pair( unigram, digrams_t() ) );
            digrams = _items.find( unigram );
            }
        string digram = make_digram( item );
        digrams_t::iterator entry = digrams->second.find( digram );
        if ( entry == digrams->second.end() ) {
            digrams->second.insert( make_pair( digram, vector<string>() ) );
            entry = digrams->second.find( digram );
            }
        entry->second.push_back( item );
        }

    int find( string& partial ) {
        string unigram = make_unigram( partial );
        unigrams_t::iterator digrams = _items.find( unigram );
        if ( digrams == _items.end() )
            return 0;
        if ( partial.length() == 1 ) {
            int digrams_found = 0;
            for ( digrams_t::iterator item = digrams->second.begin(); item != digrams->second.end(); item++ )
                digrams_found += item->second.size();
            return digrams_found;
            }
        string digram = make_digram( partial );
        digrams_t::iterator entry = digrams->second.find( digram );
        if ( entry == digrams->second.end() ) {
            if ( digrams->first.compare( 0, partial.length(), partial ) == 0 )
                return digrams->second.size();
            return 0;
            }
        int found = 0;
        vector<string> items = entry->second;
        for ( vector<string>::iterator item = items.begin(); item != items.end(); item++ )
            if ( item->compare( 0, partial.length(), partial ) == 0 )
                found += 1;
        return found;
        }
    };

int main() {
    int n;
    cin >> n;
    storage s;
    for ( int a0 = 0; a0 < n; a0++ ) {
        string op;
        string contact;
        cin >> op >> contact;
        if ( op == "add" )
            s.add( contact );
        else if ( op == "find" )
            cout << s.find( contact ) << endl;
        }
    return 0;
    }
