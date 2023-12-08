#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <limits>
#include <set>
#include <cmath>
#include <tuple>
#include <regex>
#include <cctype>
#include <functional>
#include <numeric>
#include <algorithm> 

std::map<std::string, std::pair<std::string, std::string>> locMap; 

struct Cycle { // all cycles start at a Z position
    uint index;
    uint64_t starting_z;
    uint64_t period;
};

uint64_t lcm(uint64_t a, uint64_t b) {
	return (a / std::gcd(a, b)) * b;
}

std::string editNode(std::string node, char dir) {
    if (dir == 'L') {
        return locMap.at(node).first;
    } else {
        return locMap.at(node).second;
    }
}

int main() {
    std::string filename = "input.txt"; // Change this to your input file's name
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::string instructions;
    std::getline(inputFile, instructions);
    std::vector<std::string> nodes;
    while (std::getline(inputFile, line)) {
        if (line == "") {
            continue;
        }
        std::istringstream stream(line);
        std::string key;
        std::string equal;
        std::string value1;
        std::string value2;
        stream >> key;
        stream >> equal;
        stream >> value1;
        value1 = value1.substr(1, 3);
        stream >> value2;
        value2 = value2.substr(0,3);
        locMap[key] = std::pair<std::string, std::string>(value1, value2);
        if (key[2] == 'A') {
            nodes.push_back(key);
        }
    }
    int locLen = instructions.length();
    int nodeSize = nodes.size();
    std::vector<Cycle> cycles;
    for(int i = 0; i < nodeSize; i++) {
        Cycle cycle; 
        cycle.index = i;
        std::cout << "node " << i << std::endl;
        int count = 0;
        int j = 0;
        int loc = 0;
        while (count < 2) {
            if (nodes[i][2] == 'Z') {
                std::cout << "  " << j << ": " << nodes[i] << "<-- Z location" << std::endl;
                if (count == 1) {
                    cycle.period = j - cycle.starting_z;
                    count += 1;
                }
                if (count == 0) {
                    cycle.starting_z = j;
                    count += 1;
                }
            } 
            char direction = instructions[loc];
            nodes[i] = editNode(nodes[i], direction);
            j += 1;
            loc += 1;
            if (loc == locLen) {
                loc = 0;
            }
        }
		cycles.push_back(cycle);
    }
    // find the least common multiple
    uint64_t lcm_result = 1;
    for (Cycle c : cycles) {
    	std::cout << "lcm of " << lcm_result << " and " << c.period << std::endl;
        lcm_result = lcm(lcm_result, c.period);
    	std::cout << "is " << lcm_result << std::endl;
    }
    std::cout << "lcm result " << lcm_result << std::endl;

    inputFile.close();
    return 0;
}

	
