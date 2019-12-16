/****************************************************************************
 * day2.cpp
 *
 *  Created on: 3. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2019\\day2.txt"
#define OUTPUT_VALUE 19690720

static bool prepare_file(std::vector<int>& input);
static int opcode_calculator(std::vector<int> arr);

int main(void){

	std::vector<int> arr;

	if(!prepare_file(arr)){
		return EXIT_FAILURE;
	}
	int res,res2 = 0;
	for(unsigned i=0; i<=99; i++){
		for(unsigned j=0; j<=99; j++){
			arr[1] = i;
			arr[2] = j;
			res2 = opcode_calculator(arr);
			if(res2 == OUTPUT_VALUE){
				res2 = 100*i+j;
				i = 100;
				j = 100;
			}
		}
	}
	arr[1] = 12;
	arr[2] = 2;
	res = opcode_calculator(arr);

	std::cout<<"Value left at position 0: "<<res<<std::endl;
	std::cout<<"Wanted output is produced with input combination: "<<res2<<std::endl;
	return EXIT_SUCCESS;
}

static bool prepare_file(std::vector<int>& arr){
	std::ifstream infile;
	std::string str_number;
	infile.open(FILE_LOCATION);

	if(infile.is_open()){
		while(std::getline(infile, str_number, ',')){
			arr.push_back(std::stoi(str_number));
		}
	}
	else{
		return false;
	}

	return true;
}

static int opcode_calculator(std::vector<int> arr){

	for(unsigned i=0; i<arr.size()-5; i+=4){
		switch(arr[i]){
		case 1:
			arr[arr[i+3]]=arr[arr[i+1]]+arr[arr[i+2]];
			break;
		case 2:
			arr[arr[i+3]]=arr[arr[i+1]]*arr[arr[i+2]];
			break;
		case 99:
			i = arr.size();
			break;
		default:
			std::cout<<"something went wrong!"<<std::endl;
			break;
		}
	}
	return arr[0];
}
