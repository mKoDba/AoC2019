/****************************************************************************
 * day8.cpp
 *
 *  Created on: 2. sij 2020.
 *      Author: Mario
 *
 ***************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

constexpr char const* FILE_LOCATION = "C:\\Users\\Mario\\Desktop\\aoc2019\\day8.txt";
constexpr int WIDTH = 25;
constexpr int HEIGHT = 6;

static bool parse_file(std::string& input);
static int part_one(std::string& digits);
static std::vector<char> part_two(std::string& digits);

struct DigitCount {
	int zero;
	int one;
	int two;
};

int main(void){
	std::string digits;
	std::vector<char> img;

	if(!parse_file(digits)){
		return EXIT_FAILURE;
	}
	std::cout<<"Day 8\n(Part 1) No. of 1 digits multiplied by no. of 2 digits: "<<part_one(digits)<<std::endl;
	img = part_two(digits);
	std::cout<<"(Part 2) Message produced after decoding image: "<<std::endl;
	for(unsigned i = 0; i<img.size(); ++i){
		if(i%25 == 0) std::cout<<"\n";
		std::cout << (img[i] == '1' ? "." : " ");
	}

	return EXIT_SUCCESS;
}

static bool parse_file(std::string& input){
	std::ifstream infile;

	infile.open(FILE_LOCATION);
	if(infile.is_open()){
		std::getline(infile, input);
	}
	else{
		return false;
	}
	return true;
}

static int part_one(std::string& digits){
	std::vector<std::string> layers;
	std::vector<DigitCount> counters;
	int pos = 0;
	int index_fewest = 0;
	int min = INT_MAX;
	DigitCount cnt;
	for(unsigned i = 0; i<digits.size()/(WIDTH*HEIGHT); ++i){
		std::string tmp = digits.substr(pos, WIDTH*HEIGHT);
		cnt.zero = 0;
		cnt.one = 0;
		cnt.two = 0;
		for(auto ch : tmp){
			switch(ch){
			case '0':
				cnt.zero++;
				break;
			case '1':
				cnt.one++;
				break;
			case '2':
				cnt.two++;
				break;
			default:
				break;
			}
		}
		if(cnt.zero < min) {
			min = cnt.zero;
			index_fewest = i;
		}
		counters.push_back(cnt);
		layers.push_back(tmp);
		pos = pos + WIDTH*HEIGHT;
	}
	return counters[index_fewest].one*counters[index_fewest].two;
}

static std::vector<char> part_two(std::string& digits){
	std::vector<char> decoded_chars;
	for(unsigned i = 0; i<(WIDTH*HEIGHT); ++i){
		int tmp = i;
		while(digits[tmp] == '2'){
			tmp += WIDTH*HEIGHT;
		}
		decoded_chars.push_back(digits[tmp]);
	}
	return decoded_chars;
}

