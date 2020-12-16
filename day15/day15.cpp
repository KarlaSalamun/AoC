#include <cstdio>
#include <vector>
#include <unordered_map>
#include <iostream>

int main () {
    std::vector<int> start_numbers = { 2,0,6,12,1,3 };

    std::unordered_map<int, std::vector<int>> sequence;
    for( int i=0; i<start_numbers.size(); i++ ) {
        std::vector<int> tmp_vector = { i };
        sequence.insert( { start_numbers[i], tmp_vector } );
    }
    int last_spoken = start_numbers.back();

    int turn = start_numbers.size();
    while( turn < 30000000 ) {
        if( sequence.at( last_spoken ).size() <= 1 ) {
            last_spoken = 0;
        }
        else {
            last_spoken = *(sequence.at( last_spoken ).end()-1) - *(sequence.at( last_spoken ).end()-2);
        }
        if( sequence.count( last_spoken ) == 0 ) {
            sequence.insert( { last_spoken, {turn} } );
        }
        sequence.at( last_spoken ).push_back( turn );
        turn++;
    }
    std::cout << last_spoken << std::endl;
}