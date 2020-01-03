/****************************************************************************
 * day6.cpp
 *
 *  Created on: 17. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <ctime>

constexpr char const* FILE_LOCATION = "C:\\Users\\Mario\\Desktop\\aoc2019\\day6.txt";

static bool prepare_file(std::map<std::string,std::string>& input);
static void count_orbits(std::map<std::string, std::string>& input);

int main(void){

    clock_t start = clock();
    std::map<std::string, std::string> input;

	if(!prepare_file(input)){
		return EXIT_FAILURE;
	}
	count_orbits(input);
	std::cout<<"\nduration: "<<float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC <<" ms"<<std::endl;

	return EXIT_SUCCESS;

}

static bool prepare_file(std::map<std::string, std::string>& input){
	std::ifstream infile;
	std::string line, key, value;

	infile.open(FILE_LOCATION);
	if(infile.is_open()){
	while(std::getline(infile, line)){
		value = line.substr(0,3);
		key = line.substr(4,3);
		input[key] = value;
		}
	}
	else{
		return false;
	}
	return true;
}

static void count_orbits(std::map<std::string, std::string>& input){
	std::set<std::string> san, you;
	std::vector<std::string> overlapping;
	int total = 0;
	for(auto p: input){
		if(p.first == "SAN"){
			san.insert(p.second);
		}
		if(p.first == "YOU"){
			you.insert(p.second);
		}
		++total;
		std::string tmp = p.second;
		auto it = input.find(tmp);
		while(it != input.end()){
			if(p.first == "SAN"){
				san.insert(it->second);
			}
			if(p.first == "YOU"){
				you.insert(it->second);
			}
			++total;
			tmp = it->second;
			it = input.find(tmp);
		}
	}
	std::set_intersection(san.begin(), san.end(), you.begin(), you.end(), std::back_inserter(overlapping));
	int transfers_required = san.size()+you.size()-2*overlapping.size();

	std::cout<<"Total number of orbits: "<<total<<std::endl;
	std::cout<<"Transfers required: "<<transfers_required<<std::endl;
}
