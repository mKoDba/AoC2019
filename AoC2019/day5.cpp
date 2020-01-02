/****************************************************************************
 * day5.cpp
 *
 *  Created on: 16. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/
#include "day5.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2019\\day5.txt"

static bool prepare_file(std::vector<int>& input);

int main(void){
    clock_t start = clock();

    std::vector<int> input;

	if(!prepare_file(input)){
		return EXIT_FAILURE;
	}
	IntCodeComputer comp1(input);
	IntCodeComputer comp2(input);
	comp1.run(1);
	comp2.run(5);

	std::cout<<"Day 5\n(Part 1) solution: "<<comp1.output()<<std::endl;
	std::cout<<"(Part 2) solution: "<<comp2.output()<<std::endl;

    std::cout<<"\nduration: "<<float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC <<" ms"<<std::endl;

	return EXIT_SUCCESS;
}

static bool prepare_file(std::vector<int>& input){
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
