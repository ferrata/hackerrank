#include <stack>
#include <string>
#include <iostream>

using namespace std;

char closing( char ch ) {
    if ( ch == '{' ) return '}';
    if ( ch == '(' ) return ')';
    if ( ch == '[' ) return ']';
    return ch;
    }

bool is_balanced( string expression ) {
    stack<char> stack;
    for ( string::iterator ch = expression.begin(); ch != expression.end(); ++ch ) {
        if ( *ch == '[' || *ch == '{' || *ch == '(' )
            stack.push( *ch );
        else if ( stack.empty() )
            return false;
        else {
            if ( *ch != closing( stack.top() ) )
                return false;
            stack.pop();
            }
        }
    return stack.empty();
    }

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        string expression;
        cin >> expression;
        bool answer = is_balanced(expression);
        if(answer)
            cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
    }
