/****************************************************************************
 * day7.hpp
 *
 *  Created on: 1. sij 2020.
 *      Author: Mario
 *
 ***************************************************************************/
#include <iostream>
#include <vector>

#ifndef DAY7_HPP_
#define DAY7_HPP_

class IntCodeComputer {
private:
	std::vector<int> in_codes;
	int i;
	int phase;
	int out;
	bool first_instruction;

public:
	bool stopped;
	IntCodeComputer(std::vector<int> input_codes, int ph){
		in_codes = input_codes;
		i = 0;
		phase = ph;
		out = 0;
		stopped = false;
		first_instruction = true;
	};

	int output(){
		return out;
	}

	void run(int second_stage_input){
		int opcode, mode_first, mode_second, mode_third, f, s, t;
		while(!stopped){
			opcode = in_codes[i]%100;

			mode_first = (in_codes[i]/100)%10;
			mode_second = (in_codes[i]/1000)%10;
			mode_third = (in_codes[i]/10000)%10;

			f = (mode_first) ? i+1 : in_codes[i+1];
			s = (mode_second) ? i+2 : in_codes[i+2];
			t = (mode_third) ? i+3 : in_codes[i+3];

			switch(opcode){
			case 1:
				in_codes[t]=in_codes[f]+in_codes[s];
				i += 4;
				break;
			case 2:
				in_codes[t]=in_codes[f]*in_codes[s];
				i += 4;
				break;
			case 3:
				/* when program starts, first instruction given to it is phase number,
				 * all further input instructions are output of previous stage amplifier */
				if(first_instruction){
					in_codes[in_codes[i+1]]=phase;
					first_instruction = false;
				}
				else{
					in_codes[in_codes[i+1]]=second_stage_input;
				}
				i += 2;
				break;
			case 4:
				out = in_codes[in_codes[i+1]];
				i += 2;
				return;		//after creating output, exit program without stopping it
			case 5:
				i = (in_codes[f]) ? in_codes[s] : i+3;
				break;
			case 6:
				i = (!in_codes[f]) ? in_codes[s] : i+3;
				break;
			case 7:
				in_codes[t] = (in_codes[f] < in_codes[s]) ? 1 : 0;
				i += 4;
				break;
			case 8:
				in_codes[t] = (in_codes[f] == in_codes[s]) ? 1 : 0;
				i += 4;
				break;
			case 99:
				stopped = true;
				//std::cout<<"Computer stopped..."<<std::endl;
				break;
			default:
				std::cout<<"Something went wrong!"<<std::endl;
				break;
			}
		}
	}

};



#endif /* DAY7_HPP_ */
