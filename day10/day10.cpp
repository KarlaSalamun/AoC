#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

void find_difference( std::vector<int> &adapters ) {
	std::adjacent_difference( adapters.begin(), adapters.end(), adapters.begin() );
}

std::uint64_t find_combinations( std::vector<int> &adapters ) {
	std::vector<std::uint64_t> dp;
	dp.push_back(1);

	for( auto & element : adapters ) {
		std::cout << element << " ";
	}
	std::cout << std::endl;

	dp.resize( adapters.back() + 1 );

	for( auto & adapter : adapters ) {
		for( int shift = 1; shift <= 3; shift++ ) {
			if( std::binary_search( adapters.begin(), adapters.end(), adapter - shift ) ) {
				dp[adapter] += dp[adapter-shift];
			}
		}
	}
	return dp.back();
}

int main() {
	std::ifstream infile( "input" );

	int jolts;
	std::vector<int> adapters;

	while( infile >> jolts ) {
		adapters.push_back( jolts );
	}

	adapters.insert( adapters.begin(), 0 );
	std::sort( adapters.begin(), adapters.end() );
	adapters.push_back( *(adapters.end()-1) + 3 );

	std::cout << find_combinations( adapters ) << std::endl;

	find_difference( adapters );

	int num1 = std::count( adapters.begin(), adapters.end(), 1 );

	int num3 = std::count( adapters.begin(), adapters.end(), 3 );

	std::cout << num1 * num3 << std::endl;

	return 0;
}