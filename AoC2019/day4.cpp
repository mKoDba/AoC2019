/****************************************************************************
 * day4.cpp
 *
 *  Created on: 16. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/

#include <iostream>
#include <string>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>

static int number_of_passwords(int& min, int& max, int& second_result);
static bool check_double_digits(std::vector<int>& digits, bool& passed_second);
static bool check_increasing_digits(std::vector<int>& digits);


int main(void){
	clock_t start = clock();

	const std::string input = "254032-789860";
	int min = 0, max = 0, first = 0;
	std::vector<std::string> tmp;
	boost::split(tmp, input, boost::is_any_of("-"));
	min = stoi(tmp[0]);
	max = stoi(tmp[1]);

	int second = 0;
	first = number_of_passwords(min, max, second);

	std::cout<<"Number of different passwords that meet criteria: "<<first<<std::endl;
	std::cout<<"Number of different passwords that meet all criterias: "<<second<<std::endl;
    std::cout<<"\nduration: "<<float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC <<" ms"<<std::endl;
	return EXIT_SUCCESS;

}

static int number_of_passwords(int& min, int& max, int& second){
	int tmp, first = 0;

	for(int n = min; n <= max; ++n){
		tmp = n;
		std::vector<int> digits;
		for(unsigned i = 0; i<6; ++i){
			digits.push_back(tmp%10);
			tmp /= 10;
		}
		if(check_increasing_digits(digits)){
			bool passed_second = false;
			if(check_double_digits(digits, passed_second)){
				++first;
				if(passed_second){
					++second;
				}
			}
		}

	}
	return first;
}

static bool check_double_digits(std::vector<int>& digits, bool& passed_second){
	bool same = false;
	std::map<int, int> doubles;

	for(unsigned i = 0; i<5; ++i){
		if(digits[i] == digits[i+1]){
			doubles[digits[i]]++;
			same = true;
		}
	}
	if(same){
		for(auto d: doubles){
			if(d.second == 1){
				passed_second = true;
				break;
			}
		}
	}
	return same;
}

static bool check_increasing_digits(std::vector<int>& digits){
	int min = digits[0], max = digits[0];
	bool same = true;
	for(unsigned i = 0; i < 6; ++i){
		if(digits[i] < min){
			min = digits[i];
		}
		if(digits[i] > max || digits[i] > min){	//digits inverted in vector
			same = false;
			break;
		}
	}
	return same;
}
