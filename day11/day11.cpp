#include <cstdio>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

int cnt_n( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int i=y_coord - 1;
	for(; i>=0; i--) {
		if( seats[i][x_coord] == 'L' ) {
			return 0;
		}
		if( seats[i][x_coord] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int cnt_s( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int i = y_coord + 1;
	for(; i<seats.size(); i++) {
		if( seats[i][x_coord] == 'L' ) {
			return 0;
		}
		if( seats[i][x_coord] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int cnt_e( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int j = x_coord +1;
	for(; j<seats[0].size(); j++) {
		if( seats[y_coord][j] == 'L' ) {
			return 0;
		}
		if( seats[y_coord][j] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int cnt_w( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int j = x_coord - 1;
	for(; j>=0; j--) {
		if( seats[y_coord][j] == 'L' ) {
			return 0;
		}
		if( seats[y_coord][j] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int cnt_ne( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int i =y_coord - 1;
	int j = x_coord + 1;

	for( ; i>=0 && j<seats[0].size(); i--, j++ ) {
		if( seats[i][j] == 'L' ) {
			return 0;
		}
		if( seats[i][j] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int cnt_nw( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int i = y_coord - 1;
	int j = x_coord - 1;

	for( ; i>=0 && j>=0; i--, j-- ) {
		if( seats[i][j] == 'L' ) {
			return 0;
		}
		if( seats[i][j] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int cnt_se( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int i = y_coord + 1;
	int j = x_coord + 1;

	for( ; i<seats.size() && j<seats[0].size(); i++, j++ ) {
		if( seats[i][j] == 'L' ) {
			return 0;
		}
		if( seats[i][j] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int cnt_sw( std::vector<std::string> &seats, int y_coord, int x_coord ) {
	int cnt = 0;
	int i = y_coord+1;
	int j = x_coord -1;;

	for( ; i<seats.size() && j>=0; i++, j-- ) {
		if( seats[i][j] == 'L' ) {
			return 0;
		}
		if( seats[i][j] == '#' ) {
			return 1;
		}
	}
	return 0;
}

int change_round_non_adjacent( std::vector<std::string>& old_seats, std::vector<std::string>& new_seats ) {
	int changed = 0;
	int cnt;
	bool empty;
	for( int i=0; i<old_seats.size(); i++ ) {
		for( int j=0; j<old_seats[0].size(); j++  ) {
			std::cout << i << " " << j << "\n";
			cnt = 0;
			cnt += cnt_n( old_seats, i, j );
			cnt += cnt_ne( old_seats, i, j );
			cnt += cnt_e( old_seats, i, j );
			cnt += cnt_se( old_seats, i, j );
			cnt += cnt_s( old_seats, i, j );
			cnt += cnt_sw( old_seats, i, j );
			cnt += cnt_w( old_seats, i, j );
			cnt += cnt_nw( old_seats, i, j );
			std::cout << "number of #s: "  << cnt << "\n";
			std::cout << std::endl;
			if( cnt >= 5 && old_seats[i][j] == '#' ) {
				new_seats[i][j] = 'L';
				changed++;
			}
			else if( cnt == 0 && old_seats[i][j] == 'L' ) {
				new_seats[i][j] = '#';
				changed++;
			}
		}
	}
	return changed;
}

int change_round_adjacent( std::vector<std::string>& old_seats, std::vector<std::string>& new_seats ) {
	int changed = 0;
	int cnt;
	bool empty;
	for( int i=0; i<old_seats.size(); i++ ) {
		for( int j=0; j<old_seats[0].size(); j++  ) {
			std::cout << i << " " << j << "\n";
			cnt = 0;
			int right_edge = old_seats.size()-1;
			int bottom_edge = old_seats[0].size()-1;
			for( int i_neighbor = i-1; i_neighbor<=i+1; i_neighbor++ ) {
				if( i_neighbor > right_edge || i_neighbor < 0 ) {
					continue;
				}
				for( int j_neighbor = j-1; j_neighbor<=j+1; j_neighbor++  ) {
					if( j_neighbor > bottom_edge || j_neighbor < 0 ) {
							continue;
					}
					if( j_neighbor == j && i_neighbor == i ) {
						continue;
					}
					std::cout << "neighbor at coordinate: " << i_neighbor << " " << j_neighbor << " " << old_seats[i_neighbor][j_neighbor] << "\n";
					if( old_seats[i_neighbor][j_neighbor] == '#' ) {
						cnt++;
					}
				}
			}
			std::cout << "number of #s: "  << cnt << "\n";
			std::cout << std::endl;
			if( cnt >= 4 && old_seats[i][j] == '#' ) {
				new_seats[i][j] = 'L';
				changed++;
			}
			else if( cnt == 0 && old_seats[i][j] == 'L' ) {
				new_seats[i][j] = '#';
				changed++;
			}
		}
	}
	return changed;
}

void print_seats( std::vector<std::string> seats ) {
	for( int i=0; i<seats.size(); i++) {
		std::cout << seats[i] << std::endl;
	}	
	std::cout << std::endl;
}

int main() {
	std::ifstream infile( "input" );
	std::string line;
	std::vector<std::string> seats;
	std::vector<std::string> new_seats;

	while( getline(infile, line) ) {
		seats.push_back( line );
	}

	std::copy( seats.begin(), seats.end(), std::back_inserter( new_seats ) );

	int changed = 0;
	do {
		// changed = change_round( seats, new_seats );
		changed = non_adjacent( seats, new_seats );

		seats.clear();
		std::copy( new_seats.begin(), new_seats.end(), std::back_inserter( seats ) );

		print_seats( seats );

	} while( changed != 0 );

	int sum = 0;
	for( auto & line : seats ) {
		sum += std::count( line.begin(), line.end(), '#' );
	}

	std::cout << sum << std::endl;
}