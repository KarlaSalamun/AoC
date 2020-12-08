#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <iterator>

enum class _instr { acc, nop, jmp };

struct instruction {
	_instr instr;
	int value;
};

_instr string_to_instr( std::string input ) {
	_instr instr;
	if( input == "acc" ) {
		instr = _instr::acc;
	}
	else if( input == "nop" ) {
		instr = _instr::nop;
	}
	else {
		instr = _instr::jmp;
	}
	return instr;
}

int find_acc_value( std::vector<instruction> instructions ) {

	int acc_value = 0;
	std::vector<bool> visited( instructions.size() );
	std::fill( visited.begin(), visited.end(), false );

	int pc = 0;
	while(1) {
		if( visited[pc] ) {
			return acc_value;
		}

		switch( instructions[pc].instr ) {
			case _instr::acc:
				visited[pc] = true;
				acc_value += instructions[pc].value;
				pc++;
				break;
			case _instr::nop:
				visited[pc] = true;
				pc++;
				break;
			case _instr::jmp:
				visited[pc] = true;
				pc += instructions[pc].value;
		}
	}
}

int find_corrupt_instruction( std::vector<instruction> instructions ) {
	std::vector<bool> visited( instructions.size() );

	bool b = true;

	for( int i=0; i<instructions.size(); i++ ) {
		if( instructions[i].instr == _instr::nop ) {
			instructions[i].instr = _instr::jmp;
		}
		else if( instructions[i].instr == _instr::jmp ) {
			instructions[i].instr = _instr::nop;
		}
		else {
			continue;
		}
		int pc = 0;
		int acc_value = 0;
		bool loop = false;
		std::fill( visited.begin(), visited.end(), false );
		while(pc < instructions.size()) {
			if( visited[pc] ) {
				instructions[i].instr = ( instructions[i].instr == _instr::nop ) ? _instr::jmp : _instr::nop;
				loop = true;
				break;
			}
			switch( instructions[pc].instr ) {
				case _instr::acc:
					visited[pc] = true;
					acc_value += instructions[pc].value;
					pc++;
					break;
				case _instr::nop:
					visited[pc] = true;
					pc++;
					break;
				case _instr::jmp:
					visited[pc] = true;
					pc += instructions[pc].value;
			}
		}
		if( !loop ) {
			return acc_value;
		}
	}
}

int main() {
	std::ifstream infile( "input" );

	std::vector<instruction> instructions;
	std::string instr;
	char op;
	int value;

	while( infile >> instr >> value ) {
		instructions.push_back( { string_to_instr( instr ), value } );
		std::cout << instr << " " << value << std::endl;
	}

	std::cout << find_acc_value( instructions ) << std::endl;

	std::cout << find_corrupt_instruction( instructions ) << std::endl;

	return 0;
}