#include <cstdio>
#include <iostream>
#include <fstream>

enum class _dir { north = 90, east = 0, south = 270, west = 180 };
enum class _action { move, turn };

void move_by_value( std::pair<int, int> &coordinates, _dir &orientation, char direction, int value ) {
	switch( direction ) {
		case 'N': 
			coordinates.second += value;
			break;
		case 'S':
			coordinates.second -= value;
			break;
		case 'E':
			coordinates.first += value;
			break;
		case 'W':
			coordinates.first -= value;
			break;
	}
}

void turn_ship( int value, _dir &orientation, char direction ) {
	if( direction == 'R' ) {
			value = -1 * value;
		}

		int tmp_orientation = static_cast<int>( orientation ) + value;
		tmp_orientation %= 360;
		if( tmp_orientation < 0 ) {
			tmp_orientation += 360;
		}

		orientation = static_cast<_dir>( tmp_orientation );
}

void update_ship( std::pair<int, int> &coordinates, _action action, char direction, _dir &orientation, int value ) {
	if( direction == 'F' ) {
		switch( orientation ) {
			case _dir::north:
				direction = 'N';
				break;
			case _dir::south:
				direction = 'S';
				break;
			case _dir::east:
				direction = 'E';
				break;
			case _dir::west:
				direction = 'W';
		}
	}
	if( action == _action::move ) {
		move_by_value( coordinates, orientation, direction, value );
	}
	else {
		turn_ship( value, orientation, direction );
	}
}

std::pair<int, int> turn_waypoint( const std::pair<int, int> &coordinates, int value ) {
	switch( value ) {
		case 90:
			return std::make_pair( -coordinates.second, coordinates.first );
		case 180:
			return std::make_pair( -coordinates.first, -coordinates.second );
		case 270:
			return std::make_pair( coordinates.second, -coordinates.first );
	}
	return coordinates;
}

void update_waypoint( std::pair<int, int> &coordinates, _action action, char direction, _dir &orientation, int value ) {
	if( action == _action::move ) {
		move_by_value( coordinates, orientation, direction, value );
	}
	else {
		if( direction == 'R' ) {
			value *= -1;
			if( value < 0 ) {
				value += 360;
			}
		}
		coordinates = turn_waypoint( coordinates, value );
	}
}

int compute_manhattan( std::pair<int, int> coordinates ) {
	return abs( coordinates.first ) + abs( coordinates.second );
}

int main() {
	std::ifstream infile( "input" );

	char label;
	int value;

	bool use_waypoint = true;

	std::pair<int, int> coordinates_ship;
	_dir orientation = _dir::east;
	_action action;

	if( use_waypoint ) {
		std::pair<int, int> coordinates_waypoint = { 10, 1 };
		while( infile >> label >> value ) {
			if( label == 'F' ) {
				coordinates_ship.first += coordinates_waypoint.first * value;
				coordinates_ship.second += coordinates_waypoint.second * value;
			}
			else {
				if( label == 'L' or label == 'R' ) {
					action = _action::turn;
				}
				else {
					action = _action::move;
				}
				update_waypoint( coordinates_waypoint, action, label, orientation, value );
			}

			std::cout << "ship: " << coordinates_ship.first << " " << coordinates_ship.second << std::endl;
			std::cout << "waypoint: " << coordinates_waypoint.first << " " << coordinates_waypoint.second << std::endl;
			std::cout << std::endl;
		}
	}

	else {
		while( infile >> label >> value ) {
			if( label == 'L' or label == 'R' ) {
				action = _action::turn;
			}
			else {
				action = _action::move;
			}
				update_ship( coordinates_ship, action, label, orientation, value );
			}
	}	

	std::cout << compute_manhattan( coordinates_ship ) << std::endl;

	return 0;
}