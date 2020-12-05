#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void decode_seats( std::ifstream& infile, std::vector<int>& seats ) {
	std::string line;

	while( getline( infile, line ) ) {
		int row_u = 127;
		int row_d = 0;
		int column_u = 7;
		int column_d = 0;
		int row_step = 64;
		int col_step = 4;
		for( auto & element : line )  {
			if( element == 'L' or element == 'R' ) {
				switch( element ) {
					case 'R':
						column_d = column_d + col_step;
						break;
					case 'L':
						column_u = column_d + col_step-1;
						break;
				}
				col_step /= 2;
			}
			else {
				switch( element ) {
					case 'B':
						row_d = row_d + row_step;
						break;
					case 'F':
						row_u = row_d + row_step-1;
						break;
				}
				row_step /= 2;
			}
		}
		seats.push_back( row_d * 8 + column_d );
	}
}

int find_seat( std::vector<int> seats ) {
	std::sort( seats.begin(), seats.end() );
	int lim_d = *seats.begin();
	int lim_u = *seats.end();

	int i=lim_d;

	for( auto index : seats ) {
		if( index != i ) {
			return i;
		}
		else {
			i++;
		}
	}
}

int main () {
	std::ifstream infile( "input" );

	std::vector<int> seats;

	decode_seats( infile, seats );
	int seat = find_seat( seats );

	std::vector<int>::iterator max_pos = std::max_element( seats.begin(), seats.end() );

	std::cout << *max_pos << std::endl;
	std::cout << seat << std::endl;
}