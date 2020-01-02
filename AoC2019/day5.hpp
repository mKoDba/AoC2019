/****************************************************************************
 * day5.hpp
 *
 *  Created on: 19. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/
#include <vector>
#include <iostream>

#ifndef DAY5_HPP_
#define DAY5_HPP_

class IntCodeComputer {
private:
	std::vector<int> in_codes;
	int i;
	int out;

public:
	bool stopped;
	IntCodeComputer(std::vector<int> input_codes){
		in_codes = input_codes;
		i = 0;
		out = 0;
		stopped = false;
	};

	int output(){
		return out;
	}

	void run(int input_instr){
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
				in_codes[in_codes[i+1]]=input_instr;
				i += 2;
				break;
			case 4:
				out = in_codes[in_codes[i+1]];
				i += 2;
				break;
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



#endif /* DAY5_HPP_ */
