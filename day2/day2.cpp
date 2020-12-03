#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>


bool policy1( const std::string& password, int min, int max, char c ) {
    
    int occurences = std::count( password.begin(), password.end(), c );
    return occurences >= min && occurences <= max;
}

bool policy2( const std::string& password, int index1, int index2, char c ) {
    return password.at( index1 - 1 ) == c xor password.at( index2 - 1 ) == c;
}


int main (void) {
    
    std::ifstream infile ( "input" );

    int lim_min, lim_max;
    char tmp;
    char c;
    std::string password;
    int valid_counter1 = 0;
    int valid_counter2 = 0;

    while( infile >> lim_min >> tmp >> lim_max >> c >> tmp >> password ) {

        if( policy1( password, lim_min, lim_max, c ) ) {
            valid_counter1++;
        }
        if( policy2( password, lim_min, lim_max, c ) ) {
            valid_counter2++;
        }
    }
    
    std::cout << valid_counter1 << "\n";
    std::cout << valid_counter2 << "\n";

    return 0;
}