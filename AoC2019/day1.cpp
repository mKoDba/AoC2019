/****************************************************************************
 * day1.cpp
 *
 *  Created on: 1. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/

#include <fstream>
#include <iostream>
#include <cmath>

//using namespace std;
#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2019\\day1.txt"

int main(void){

	std::ifstream inFile;
	std::string input;
	double mass = 0;
	double fuel_sum = 0;

	inFile.open(FILE_LOCATION);
	if(inFile.is_open()){
		while(std::getline(inFile, input)){
			mass = stod(input);
			while(mass > 0){
				mass = (floor(mass/3))-2;
				if(mass > 0){
					fuel_sum += mass;
				}
			}
		}
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}

	std::cout<<std::fixed<<"Total fuel requirements:  "<<fuel_sum<<std::endl;

	return 0;
}

