#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <utility>
#include <queue>
#include <boost/algorithm/string.hpp>

struct Bag {
	int number;
	std::string color;
};

bool found_bag( std::unordered_map<std::string, std::vector<Bag>> &map, std::string start, const std::string &end ) {
	std::queue<std::string> Q;
	if( start == end ) {
		return false;
	}
	Q.push( start );
	while( !Q.empty() ) {
		start = Q.front();
		Q.pop();

		for( const auto &child : map.at( start ) ) {
			Q.push( child.color );
		}
		if( start == end ) {
			return true;
		}
	}
	return false;
}

int count_containing( const std::unordered_map<std::string, std::vector<Bag>> &map, const std::string &start ) {
    int sum = 0;
    for( const auto &child : map.at( start ) ) {
        sum += child.number + child.number * count_containing( map, child.color );
    }
    return sum;
}

int main() {

	std::unordered_map<std::string, std::vector<Bag>> map;
	std::ifstream infile( "input" );

	std::string line;

	while( getline( infile, line ) ) {
        std::vector<std::string> line_split;
        std::vector<std::string> root_split;
		boost::split( line_split, line, boost::is_any_of( "," ) );

		boost::split( root_split, line_split[0], boost::is_any_of( " " ) );
		root_split[0].append( root_split[1] );
		root_split[5].append( root_split[6] );

        std::vector<Bag> values;
        if( root_split[4] != "no" ) {
            values.push_back( { std::atoi( root_split[4].c_str() ), root_split[5] } );
            for( int i=1; i<line_split.size(); i++ ) {
                std::vector<std::string> leaves;
                boost::split( leaves, line_split[i], boost::is_any_of(" ") );
                leaves[2].append( leaves[3] );
                values.push_back( { std::atoi( leaves[1].c_str() ), leaves[2] } );
            }
        }
		map.insert( std::make_pair( root_split[0], values ) );
	}


    int counter = std::count_if( map.cbegin(), map.cend(),
            [&map]( const auto &k ) { return found_bag( map, k.first, "shinygold" ); } );


    std::cout << counter << std::endl;

    counter = count_containing( map, "shinygold" );

    std::cout << counter << std::endl;

	return 0;
}
