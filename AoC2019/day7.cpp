/****************************************************************************
 * day7.cpp
 *
 *  Created on: 1. sij 2020.
 *      Author: Mario
 *
 ***************************************************************************/
#include "day7.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <algorithm>

#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2019\\day7.txt"

static bool parse_file(std::vector<int>& input);
static void part_one(std::vector<int> in_codes);
static void part_two(std::vector<int> in_codes);

int main(void){

    std::vector<int> input;

	if(!parse_file(input)){
		return EXIT_FAILURE;
	}
	part_one(input);
	part_two(input);

	return EXIT_SUCCESS;
}

static bool parse_file(std::vector<int>& input){
	std::ifstream infile;
	std::string num;

	infile.open(FILE_LOCATION);
	if(infile.is_open()){
		while(std::getline(infile, num, ',')){
			input.push_back(std::stoi(num));
		}
	}
	else{
		return false;
	}
	return true;
}

static void part_one(std::vector<int> in_codes){
	int max = INT_MIN;
	std::array<int, 5> phase = {0,1,2,3,4};
	/* initialize IntCodeComputers with copy of input instructions and phase number to each computer */
	while(std::next_permutation(phase.begin(), phase.end())){
		IntCodeComputer A(in_codes, phase[0]);
		IntCodeComputer B(in_codes, phase[1]);
		IntCodeComputer C(in_codes, phase[2]);
		IntCodeComputer D(in_codes, phase[3]);
		IntCodeComputer E(in_codes, phase[4]);

		A.run(E.output());
		B.run(A.output());
		C.run(B.output());
		D.run(C.output());
		E.run(D.output());
		if(E.output() > max){
			max = E.output();
		}
	}
	std::cout<<"(Part 1) Highest signal that can be sent to thrusters: "<<max<<std::endl;

}

static void part_two(std::vector<int> in_codes){
	int max = INT_MIN;
	std::array<int, 5> phase = {5,6,7,8,9};
	/* initialize IntCodeComputers with copy of input instructions and phase number to each computer */
	while(std::next_permutation(phase.begin(), phase.end())){
		IntCodeComputer A(in_codes, phase[0]);
		IntCodeComputer B(in_codes, phase[1]);
		IntCodeComputer C(in_codes, phase[2]);
		IntCodeComputer D(in_codes, phase[3]);
		IntCodeComputer E(in_codes, phase[4]);

		while(!E.stopped){
			A.run(E.output());
			B.run(A.output());
			C.run(B.output());
			D.run(C.output());
			E.run(D.output());
			if(E.output() > max){
				max = E.output();
			}
		}

	}
	std::cout<<"(Part 2) Highest signal that can be sent to thrusters: "<<max<<std::endl;

}

