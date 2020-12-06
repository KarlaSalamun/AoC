#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int answers_any( std::vector<char> answers ) {
	std::sort( answers.begin(), answers.end() );
	auto last = std::unique( answers.begin(), answers.end() );
	answers.erase( last, answers.end() );

	return answers.size();
}

int answers_all( std::vector<char> answers, int line_cnt ) {
	std::vector<int> chars_map( 128 );
	std::fill( chars_map.begin(), chars_map.end(), 0 );

	std::for_each( answers.cbegin(), answers.cend(), 
		[&chars_map]( const auto &i ) { chars_map[ i - 'a' ]++; } );

	return std::count( chars_map.begin(), chars_map.end(), line_cnt );
}

int main() {
	std::ifstream infile( "input" );

	std::string line;
	std::vector<char> answers;

	int any_counter = 0;
	int all_counter = 0;
	int line_counter = 0;

	while( getline( infile, line ) ) {
		if( !line.empty() ) {
			line_counter++;
			for( auto & element : line ) {
				answers.push_back( element );
			}
		}
		else {
			any_counter += answers_any( answers );
			all_counter += answers_all( answers, line_counter );
			answers.clear();
			line_counter = 0;
		}
	}
	any_counter += answers_any( answers );
	all_counter += answers_all( answers, line_counter );
	std::cout << any_counter << std::endl;
	std::cout << all_counter << std::endl;
} 