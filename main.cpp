#include <iostream>
#include <fstream>

#include "kami_state.h"

using namespace std;

constexpr int MAX_STEP = 30;

bool dfs( KamiState const &original_state, int *result, int max_step)
{
}

int main( int argc, char **argv)
{
    KamiState state;
    if ( argc > 1) {
        ifstream fin( argv[ 1]);
        state = KamiState::read_state( fin);
    } else {
        state = KamiState::read_state( cin);
    }
    int result[ MAX_STEP];
    for ( int max_step = 1; max_step <= MAX_STEP; max_step ++) {
        cout << "trying to solve in " << max_step << " step(s)..." << endl;
        if ( dfs( state, result, max_step)) {
            //output result
            break;
        }
    }
    return 0;
}

