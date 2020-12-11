#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

std::uint64_t find_invalid( std::vector<std::uint64_t> numbers ) {
	int preamble_size = 25;
	for( int current = preamble_size; current < numbers.size(); current++ ) {
		bool found = false;
		for( int i=current - preamble_size; i<current; i++ ) {
			for( int j=current - preamble_size; j<current; j++ ) {
				if( i==j ) {
					continue;
				}
				if( numbers[i] + numbers[j] == numbers[current] ) {
					found = true;
					break;
				}
			}
			if( found ) {
				break;
			}
		}
		if( !found ) {
			return numbers[current];
		}
	}
	return -1;
}

std::uint64_t find_set( std::vector<std::uint64_t> numbers, std::uint64_t value ) {
	for(int set_size = 2; set_size < numbers.size(); set_size++) {
		for( int num_index = 0; num_index <= numbers.size() - set_size; num_index++ ) {
			std::uint64_t sum = std::accumulate( numbers.begin() + num_index, 
				numbers.begin() + num_index + set_size, 0 );
			if( sum == value ) {
				std::uint64_t min = *std::min_element( numbers.begin() + num_index,
				 	numbers.begin() + num_index + set_size);

				std::uint64_t max = *std::max_element( numbers.begin() + num_index,
				 	numbers.begin() + num_index + set_size);
				return min + max;
			}
		}
	}
	return -1;
}

int main() {
	std::ifstream infile("input");
	std::uint64_t current_num;
	std::vector<std::uint64_t> numbers;

	while(infile >> current_num ) {
		numbers.push_back( current_num );
	}

	std::uint64_t invalid = find_invalid( numbers );

	std::cout << invalid << std::endl;

	std::cout << find_set( numbers, invalid ) << std::endl;
}