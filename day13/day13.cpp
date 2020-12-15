#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <algorithm>

struct Bus{
	int bus_id;
	int minute;
};

void find_bus( const std::vector<Bus> &schedule, const int &time, int &id, int &wait_mins ) {
	std::vector<int> time_diff(schedule.size());
	std::vector<int> departures;
	for( auto &element : schedule ) {
		int closest = time / element.bus_id;
		closest = ( closest + 1 ) * element.bus_id;
		departures.push_back( closest );
	}
	std::transform( departures.begin(), departures.end(), time_diff.begin(), [time](int x) -> int { return x - time; } );
	auto min = std::min_element( time_diff.begin(), time_diff.end() );
	int index = std::distance( time_diff.begin(), min );

	id = schedule[index].bus_id;

	wait_mins = departures[index] - time;
}

std::uint64_t find_timestamp( const std::vector<Bus> &schedule ) {
	uint64_t timestamp = 0;
	bool timestamp_found = false;
	uint64_t step;

	step = 1;
	uint64_t result = 0;

	// timestamp = schedule[0].bus_id;
	timestamp = 100000000000000;
	while( timestamp % schedule[0].bus_id != 0 ) {
		timestamp++;
	}
	step = schedule[0].bus_id;

	for( int i=1; i<schedule.size(); i++ ) {
		while( timestamp % schedule[i].bus_id != schedule[i].minute ) {
			timestamp += step;
		}
		int index = i-1;
		step = schedule[0].bus_id;
		for( int j=i; j>0; j-- ) {
			step *= schedule[j].bus_id;
		}
		std::cout << step << std::endl;
	}
	return timestamp;
}

int main(void) {
	std::ifstream infile( "input" );
	std::string line;

	int time;
	getline( infile, line );

	time = std::atoi( line.c_str() );
	std::vector<std::string> entries;

	std::vector<Bus> buses;

	getline( infile, line );
	boost::split( entries, line, boost::is_any_of( "," ) );

	for( int i=0; i<entries.size(); i++ ) {
		if( entries[i] == "x" ) {
			continue;
		}
		else {
			int bus_id = std::atoi( entries[i].c_str() );
			buses.push_back( { bus_id, (bus_id - i % bus_id ) % bus_id } );
		}
	}

	int id, wait_mins;

	find_bus( buses, time, id, wait_mins );
	std::uint64_t sequence = find_timestamp( buses );

	std::cout << id * wait_mins << std::endl;
	std::cout << sequence << std::endl;

	return 0;
}
