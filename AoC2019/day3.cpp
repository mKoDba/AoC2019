/****************************************************************************
 * day3.cpp
 *
 *  Created on: 13. pro 2019.
 *      Author: Mario
 *
 ***************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <ctime>
#include <map>

constexpr char const* FILE_LOCATION = "C:\\Users\\Mario\\Desktop\\aoc2019\\day3.txt";

static bool prepare_file(std::vector<int>& arr, std::vector<std::pair<char, int>>& wire_1, std::vector<std::pair<char, int>>& wire_2);
static int find_intersection(std::vector<std::pair<char, int>>& wire_1, std::vector<std::pair<char, int>>& wire_2, int& fewest);
static void manh_distance(std::pair<int, int>& cur_pos, int& shortest_dist);
static void fewest_steps(std::pair<int, int>& cur_pos, std::map<std::pair<int, int>, int>& wire1_steps, std::map<std::pair<int, int>, int>& wire2_steps, int& fewest);

int main(void){
    clock_t start = clock();
    int fewest = INT_MAX;
	std::vector<int> arr;
	std::vector<std::pair<char, int>> wire_1, wire_2;

	if(!prepare_file(arr, wire_1, wire_2)){
		return EXIT_FAILURE;
	}
	int manh_dist = find_intersection(wire_1, wire_2, fewest);

    std::cout<<"\nduration: "<<float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC <<" ms"<<std::endl;
	std::cout<<"Manhattan distance from central port to closest intersection is: "<<manh_dist<<std::endl;
	std::cout<<"Fewest combined steps the wires must take to reach an intersection: "<<fewest<<std::endl;

	return EXIT_SUCCESS;
}

static bool prepare_file(std::vector<int>& arr, std::vector<std::pair<char, int>>& wire_1, std::vector<std::pair<char, int>>& wire_2){
	std::ifstream infile;
	std::vector<std::string> wires,wire_1_str,wire_2_str;
	std::string w;
	char dir;
	infile.open(FILE_LOCATION);

	if(infile.is_open()){
		while(std::getline(infile, w, '.')){
			wires.push_back(w);
		}
		boost::split(wire_1_str, wires[0], boost::is_any_of(","));
		for(auto it: wire_1_str){
			dir = it.at(0);
			it.erase(0,1);
			wire_1.push_back(std::make_pair(dir, std::stoi(it)));
		}


		boost::split(wire_2_str, wires[1], boost::is_any_of(","));
		wire_2_str[0].erase(0,1);	// deleting '/n' on the first string
		for(auto it: wire_2_str){
			dir = it.at(0);
			it.erase(0,1);
			wire_2.push_back(std::make_pair(dir, std::stoi(it)));
		}
	}
	else{
		return false;
	}

	return true;
}

static int find_intersection(std::vector<std::pair<char, int>>& wire_1, std::vector<std::pair<char, int>>& wire_2, int& fewest){
	std::map<std::pair<int, int>, int> visited;
	std::map<std::pair<int, int>, int> wire1_steps, wire2_steps;
	std::pair<int, int> cur_pos = {0,0};	// {x,y} coordinate system
	char dir;
	int dist,steps = 0;
	for(auto const& p: wire_1){
		dir = p.first;
		dist = p.second;
		while(dist){
			switch(dir){
			case 'R':
				cur_pos.first++;
				break;
			case 'L':
				cur_pos.first--;
				break;
			case 'U':
				cur_pos.second++;
				break;
			case 'D':
				cur_pos.second--;
				break;
			}
			visited[cur_pos]++;
			--dist;

			++steps;
			wire1_steps[cur_pos] = steps;
		}
	}

	int shortest_dist = INT_MAX;
	steps = 0;
	cur_pos = {0,0};
	for(auto const& p: wire_2){
		dir = p.first;
		dist = p.second;
		while(dist){
			switch(dir){
			case 'R':
				cur_pos.first++;
				break;
			case 'L':
				cur_pos.first--;
				break;
			case 'U':
				cur_pos.second++;
				break;
			case 'D':
				cur_pos.second--;
				break;
			}
			--dist;

			++steps;
			wire2_steps[cur_pos] = steps;

			if(visited[cur_pos]){
				manh_distance(cur_pos, shortest_dist);
				fewest_steps(cur_pos, wire1_steps, wire2_steps, fewest);
			}
		}
	}

	return shortest_dist;

}


static void manh_distance(std::pair<int, int>& cur_pos, int& shortest_dist){
	int tmp = std::abs(cur_pos.first-0)+std::abs(cur_pos.second-0);
	if(tmp < shortest_dist){
		shortest_dist = tmp;
	}
}

static void fewest_steps(std::pair<int, int>& cur_pos, std::map<std::pair<int, int>, int>& wire1_steps, std::map<std::pair<int, int>, int>& wire2_steps, int& fewest){
	int tmp = wire1_steps[cur_pos] + wire2_steps[cur_pos];
	if(tmp < fewest){
		fewest = tmp;
	}
}
