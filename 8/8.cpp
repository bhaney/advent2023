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

std::map<std::string, std::pair<std::string, std::string>> locMap; 

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
    }
    uint64_t count = 0;
    int loc = 0;
    int locLen = instructions.length();
    std::string start = "AAA";
    std::string end = "ZZZ";
    while (start != end) {
        count += 1;
        char direction = instructions[loc];
        std::pair<std::string, std::string> options = locMap.at(start);
        if (direction == 'L') {
            start = options.first;
        } else {
            start = options.second;
        }
        loc += 1;
        if (loc == locLen) {
            loc = 0;
        }
    }
    std::cout << "count is: " << count << std::endl;
    inputFile.close();
    return 0;
}

	
