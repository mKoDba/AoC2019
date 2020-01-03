/****************************************************************************
 * day9.cpp
 *
 *  Created on: 2. sij 2020.
 *      Author: Mario
 *
 ***************************************************************************/
#include "day9.hpp"

#include <iostream>
#include <vector>
#include <fstream>

typedef long long ll;
constexpr char const* FILE_LOCATION = "C:\\Users\\Mario\\Desktop\\aoc2019\\day9.txt";
constexpr int TEST_MODE = 1;
constexpr int BOOST_MODE = 2;
constexpr int FILL_SIZE = 100000000;

static bool parse_file(std::vector<ll>& input);

int main(void){

    std::vector<ll> input;

	if(!parse_file(input)){
		return EXIT_FAILURE;
	}
	//add 0s to input to make accessible area bigger
	for(unsigned i = 0; i < FILL_SIZE; ++i){
		input.push_back(0);
	}
	IntCodeComputer Machine1(input);
	IntCodeComputer Machine2(input);

	Machine1.run(TEST_MODE);
	std::cout<<"Day 9\n(Part 1) Produced BOOST keycode: "<<Machine1.output()<<std::endl;

	Machine2.run(BOOST_MODE);
	std::cout<<"(Part 2) Coordinates of the distress signal: "<<Machine2.output()<<std::endl;

	return EXIT_SUCCESS;
}

static bool parse_file(std::vector<ll>& input){
	std::ifstream infile;
	std::string num;

	infile.open(FILE_LOCATION);
	if(infile.is_open()){
		while(std::getline(infile, num, ',')){
			input.push_back(std::stoll(num));
		}
	}
	else{
		return false;
	}
	return true;
}
