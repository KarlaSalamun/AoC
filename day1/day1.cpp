#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

void find_pairs( std::vector<int> entries ) {
	for( auto i=0; i<entries.size(); i++ ) {
		for( auto j=i+1; j<entries.size(); j++ ) {
			if( entries[i] + entries[j] == 2020 ) {
				std::cout << entries[i] << "\t" << entries[j] << "\n";
				std::cout << ( entries[i] * entries[j] ) << "\n";
				return;
			}
		}
	}
}

void find_triplets( std::vector<int> entries ) {
	std::sort( entries.begin(), entries.end() );

	for( auto i=0; i<entries.size(); i++ ) {
		int j=i+1;
		int k=entries.size()-1;
		while(1) {
			int sum = entries[i] + entries[j] + entries[k];
			if( sum == 2020 ) {
				std::cout << entries[i] << "\t" << entries[j] << "\t" << entries[k] << "\n";
				std::cout << ( entries[i] * entries[j] * entries[k] ) << "\n";
				return;
			}
			else if( sum < 2020 ) {
				j++;
				if( j == k ) {
					break;
				}
			}
			else {
				k--;
				if( k == j ) {
					break;
				}
			}
		}
	}
}

int main() {

	int entry;

	std::vector<int> entries;
	std::ifstream infile("input");

	while( infile >> entry ) {
		entries.push_back( entry );
	}

	find_pairs( entries );
 	find_triplets( entries );

	return 0;
}