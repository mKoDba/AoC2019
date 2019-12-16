/****************************************************************************
 * day5.cpp
 *
 *  Created on: 16. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2019\\day5.txt"

static void opcode_calculator(std::vector<int>& input);
static bool prepare_file(std::vector<int>& input);

int main(void){
    clock_t start = clock();

    std::vector<int> input;

	if(!prepare_file(input)){
		return EXIT_FAILURE;
	}
	opcode_calculator(input);

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

static void opcode_calculator(std::vector<int>& input){
	unsigned i = 0;
	while(input[i]%100 != 99){
		int code = input[i]%100;
		int mode_first = (input[i]/100)%10;
		int mode_second = (input[i]/1000)%10;
		int mode_third = (input[i]/10000)%10;
		int f,s,t;

		if(!mode_first){
			f = input[i+1];
		}
		else{
			f = i+1;
		}
		if(!mode_second){
			s = input[i+2];
		}
		else{
			s = i+2;
		}
		if(!mode_third){
			t = input[i+3];
		}
		else{
			t = i+3;
		}
		//std::cout<<"trying code..\n";
		switch(code){
		case 1:
			input[t]=input[f]+input[s];
			i += 4;
			break;
		case 2:
			input[t]=input[f]*input[s];
			i += 4;
			break;
		case 3:
			input[input[i+1]]=5;	//as specified by program
			i += 2;
			break;
		case 4:
			std::cout<<input[input[i+1]]<<std::endl;
			i += 2;
			break;
		case 5:
			if(input[f]){
				i = input[s];
			}
			else{
				i += 3;
			}
			break;
		case 6:
			if(!input[f]){
				i = input[s];
			}
			else{
				i += 3;
			}
			break;
		case 7:
			if(input[f] < input[s]){
				input[t] = 1;
			}
			else{
				input[t] = 0;
			}
			i += 4;
			break;
		case 8:
			if(input[f] == input[s]){
				input[t] = 1;
			}
			else{
				input[t] = 0;
			}
			i += 4;
			break;
		default:
			std::cout<<"something went wrong!"<<std::endl;
			break;
		}
	}
}
