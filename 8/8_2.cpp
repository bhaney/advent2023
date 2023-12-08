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

int countNodes(std::vector<std::string>& places) {
    int count = 0;
    for (const std::string& s : places) {
        if (s[2] == 'Z') {
            count += 1;
        }
    }
    return count;
}

void changeNodes(std::vector<std::string>& nodes, std::map<std::string, std::pair<std::string, std::string>>& mapLoc, char dir) {
    for (int i = 0; i < nodes.size(); i++) {
        if (dir == 'L') {
            nodes[i] = mapLoc.at(nodes[i]).first;
        } else {
            nodes[i] = mapLoc.at(nodes[i]).second;
        }
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
    uint64_t count = 0;
    int loc = 0;
    int locLen = instructions.length();
    int nodeSize = nodes.size();
    while (countNodes(nodes) != nodeSize) {
        count += 1;
        char direction = instructions[loc];
        if (direction == 'L') {
            changeNodes(nodes, locMap, 'L');
        } else {
            changeNodes(nodes, locMap, 'R');
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

	
