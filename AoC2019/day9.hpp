/****************************************************************************
 * day9.hpp
 *
 *  Created on: 2. sij 2020.
 *      Author: Mario
 *
 ***************************************************************************/
#include <vector>
#include <iostream>

#ifndef DAY9_HPP_
#define DAY9_HPP_

typedef long long ll;

class IntCodeComputer {
private:
	std::vector<ll> in_codes;
	int i;
	ll out;
	ll relative;

public:
	bool stopped;
	IntCodeComputer(std::vector<ll> input_codes){
		in_codes = input_codes;
		i = 0;
		out = 0;
		relative = 0;
		stopped = false;
	};

	ll output(){
		return out;
	}

	/* parameter value:
	 * 		0 - position mode
	 *		1 - immediate mode
	 *	 	2 - relative mode
	 */
	ll parameter_mode(int param, ll ind){
		ll index;
		if(param == 0){
			index = in_codes[ind];
		}
		else if(param == 1){
			index = ind;
		}
		else{
			index = relative + in_codes[ind];
		}
		return index;
	}

	void run(int input_instr){
		int opcode, mode_first, mode_second, mode_third;
		ll f, s, t;
		while(!stopped){
			opcode = in_codes[i]%100;

			mode_first = (in_codes[i]/100)%10;
			mode_second = (in_codes[i]/1000)%10;
			mode_third = (in_codes[i]/10000)%10;

			f = parameter_mode(mode_first, i+1);
			s = parameter_mode(mode_second, i+2);
			t = parameter_mode(mode_third, i+3);

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
				in_codes[f]=input_instr;
				i += 2;
				break;
			case 4:
				out = in_codes[f];
				//std::cout<<out<<std::endl;
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
			case 9:
				relative += in_codes[f];
				i += 2;
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

#endif /* DAY9_HPP_ */
