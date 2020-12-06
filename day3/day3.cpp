#include <fstream>
#include <iostream>
#include <sstream>
#include <ostream>
#include <cstring>
#include <vector>

int count_trees( const std::vector<std::string> map, int x_step, int y_step ) {

	std::string line;

	int x_index = 0;
	int y_index = 0;
	int trees = 0;

	for( y_index = 0; y_index < map.size(); y_index+=y_step ) {
		std::string line = map.at(y_index);
		if( line.at( x_index ) == '#' ) {
			trees++;
		}
		x_index += x_step;
		if( x_index >= line.size() ) {
			x_index %= ( line.size() );
		}
	}

	return trees;
}

int main (void) {
	std::ifstream infile( "input" );
	long long int trees;

	std::string line;

	std::vector<std::string> map;

	while( std::getline( infile, line ) ) {
		map.push_back( line );
	}

	trees = count_trees( map, 3, 1 ) * count_trees( map, 1, 1 )
		 * count_trees( map, 5, 1 ) * count_trees( map, 7, 1 )
		 * count_trees( map, 1, 2 );

	std::cout << trees << std::endl;
}
