#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <string>

bool check_entry( std::string entry ) {
	std::string token = entry.substr(0, entry.find(":"));
	std::string value = entry.substr( entry.find(":") + 1, entry.size() );

	if( std::regex_match( token, std::regex( "hgt" ) ) ) {
		if( std::regex_match( value, std::regex( "^1[5-8][0-9]cm$|^19[0-3]cm$" ))) {
			// std::cout << value << std::endl;
			return true;
		}
		if( std::regex_match( value, std::regex("^59in$|^6[0-9]in$|^7[0-6]in$" )) ){
			// std::cout << value << std::endl;
			return true;
		}
	}

	else if( std::regex_match( token, std::regex( "byr" ) ) 
		and std::regex_match( value, std::regex( "^19[2-9][0-9]$|^200[0-2]$" ) )) {
			// std::cout << value << std::endl;
			return true;
	}

	else if( std::regex_match( token, std::regex( "iyr" ) ) 
		and std::regex_match( value, std::regex( "^201[0-9]$|^2020$" ) )) {
			return true;
	}

	else if( std::regex_match( token, std::regex( "eyr" ) ) 
		and std::regex_match( value, std::regex( "^202[0-9]$|^2030$" ) )) {
			return true;
	}

	else if( std::regex_match( token, std::regex( "hcl" ) ) 
		and ( std::regex_match( value, std::regex( "#[0-9a-f]{6}" ) ) )) {
			return true;
	}

	else if( std::regex_match( token, std::regex( "ecl" ) ) 
		and std::regex_match( value, std::regex( "^amb$|^blu$|^brn$|^gry$|^grn$|^hzl$|^oth$" ) ) ) {
			return true;
	}

	else if( std::regex_match( token, std::regex( "pid" ) ) 
		and std::regex_match( value, std::regex( "[0-9]{9}" ) )) {
				return true;
	}

	else if( std::regex_match( token, std::regex( "cid" ) )) {
		return true;
	}

	std::cout << entry << std::endl;

	return false;
}

int main () {
	std::ifstream infile( "input" );

	std::string line;
	std::vector<std::string> passport_1 = { "byr", "iyr", "eyr", "hgt", "hcl", 
		"ecl", "pid", "cid" };

	std::vector<std::string> passport_2 = { "byr", "iyr", "eyr", "hgt", "hcl", 
		"ecl", "pid" };

	std::sort( passport_1.begin(), passport_1.end() );
	std::sort( passport_2.begin(), passport_2.end() );

	std::vector<std::string> tokens;

	int valid_cnt = 0;

	bool valid_tokens = true;
	bool valid_passports = true;

	while( getline( infile, line ) ) {

		size_t pos = 0;
		std::string entry;

		if( !line.empty() ) {
			if( valid_tokens ) {
				std::stringstream ss(line);

				while( ss >> entry ) {
					std::string token = entry.substr(0, entry.find(":"));

					if( check_entry( entry ) ) {
			    		tokens.push_back( token );
					}
					else {
						valid_tokens = false;
						tokens.clear();
						break;
					}
				}
			}
		}

		else {
			valid_passports = true;
			if( valid_tokens ) {
				if ( tokens.size() == 8 ) {
					valid_cnt++;
				}
				else if( tokens.size() == 7 ) {
					std::sort( tokens.begin(), tokens.end() );
					for( auto & token : passport_2 ) {
						if( std::find( tokens.begin(), tokens.end(), token ) == tokens.end() ) {
							valid_passports = false;
							break;
						}
					}
					if( valid_passports ) {
						valid_cnt++;
					}
				}
			}
			tokens.clear();
			valid_tokens = true;
		}
	}
	valid_passports = true;
	if( valid_tokens ) {
		if ( tokens.size() == 8 ) {
			valid_cnt++;
		}
		else if( tokens.size() == 7 ) {
			std::sort( tokens.begin(), tokens.end() );
			for( auto & token : passport_2 ) {
				if( std::find( tokens.begin(), tokens.end(), token ) == tokens.end() ) {
					valid_passports = false;
					break;
				}
			}
			if( valid_passports ) {
				valid_cnt++;
			}
		}
	}
	tokens.clear();
	valid_tokens = true;

	std::cout << valid_cnt << std::endl;
}