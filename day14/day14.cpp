#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <regex>
#include <cassert>

void to_binary( std::vector<char> &binary, uint64_t number ) {
    binary.assign( 36, '0' );
    int exp = 2;
    for( int i=35; i>=0; i-- ) {
        if( number % exp ) {
            binary[i] = '1';
        }
        number /= 2;
    }
}

uint64_t to_integer( std::vector<char> binary ) {
    uint64_t number = 0;
    uint64_t exp = 1;
    for( int i=35; i>=0; i-- ) {
        if( binary[i] == '1' ) {
            number += exp;
        }
        exp *= 2;
    }
    return number;
}

uint64_t compute_sum( std::unordered_map<uint64_t, std::vector<char>> locations ) {
    uint64_t sum = 0;
    for( auto &element: locations ) {
        sum += to_integer( element.second );
    }
    assert( sum > 0 );
    return sum;
}

void execute_program( std::string mask, std::vector<std::pair<uint64_t, std::vector<char>>> memory, std::unordered_map<uint64_t, std::vector<char>> &locations ) {

    for( auto & element : memory ) {
        int size = element.second.size();
        std::vector<char> tmp_vector(36);
        for( int i=0; i<36; i++ ) {
            tmp_vector[i] = element.second[i];
        }
        for( int i=0; i<36; i++ ) {
            if( mask[i] != 'X' ) {
                tmp_vector[i] = mask[i];
            }
        }

        std::cout << element.first << " ";
        for( int i=0; i<tmp_vector.size(); i++ ) {
            std::cout << tmp_vector[i];
        }
        std::cout << std::endl;
        if( locations.count( element.first ) ) {
            locations.erase( element.first );
        }
        locations.insert( { element.first, tmp_vector } );
    }
}

int main () {
    std::ifstream infile( "input" );
    std::string line;
    std::vector<std::string> split;
    std::vector<std::pair<uint64_t, std::vector<char>>> memory;
    std::string mask;

    uint64_t sum;
    std::unordered_map<uint64_t, std::vector<char>> locations;

    while( getline( infile, line ) )  {
        if( std::regex_match( line, std::regex( ".*[\[].*" ) ) ) {
            std::vector<std::string> split;
            boost::split( split, line, boost::is_any_of("[]") );
            uint64_t location = std::atoi(split[1].c_str());
            boost::split( split, split[2], boost::is_any_of( " " ) );
            std::vector<char> binary_num;
            to_binary( binary_num, std::atoi( split[2].c_str() ) );
            memory.push_back( std::make_pair( location, binary_num ) );
        }
        else {
            if( !mask.empty() ) {
                execute_program( mask, memory, locations );
                mask.clear();
                memory.clear();
            }
            std::vector<std::string> split;
            boost::split( split, line, boost::is_any_of(" ") );
            std::copy( split[2].begin(), split[2].end(), std::back_inserter( mask ) );
        }
    }

    execute_program( mask, memory, locations );
    sum = compute_sum( locations );
    std::cout << sum << std::endl;

    return 0;
}