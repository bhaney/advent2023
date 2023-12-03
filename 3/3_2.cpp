#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <tuple>
#include <regex>
#include <cctype>

int findNumber(int i, int length, std::string& line) {
    int left_limit = i;
    int right_limit = i;
    while (left_limit > 0 && std::isdigit(line[left_limit-1])) {
        left_limit -= 1;
    }
    while (right_limit < length-1 && std::isdigit(line[right_limit+1])) {
        right_limit += 1;
    }
    int num_len = right_limit-left_limit+1;
    int num = std::stoi(line.substr(left_limit, num_len));
    std::cout << "part " << num << " is a valid number" << std::endl;
    std::string replacement(num_len, '.');
    line.replace(left_limit, num_len, replacement);
    return num;
}

std::vector<int> getNumbers(int i, int length, std::string prev_line, std::string curr_line, std::string next_line) {
    // look in the area around index i, taking into account edges
    std::vector<int> numbers;
    // 8 cases
    if (i-1 >= 0 && prev_line != "") { // upper left
        char c = prev_line[i-1];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i-1, length, prev_line));
        }
    }
    if (prev_line != "") { // upper center
        char c = prev_line[i];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i, length, prev_line));
        }
    }
    if (i+1 < length && prev_line != "") { // upper right
        char c = prev_line[i+1];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i+1, length, prev_line));
        }
    }
    if (i-1 >= 0) { // left
        char c = curr_line[i-1];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i-1, length, curr_line));
        }
    }
    if (i+1 < length) { // right
        char c = curr_line[i+1];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i+1, length, curr_line));
        }
    }
    if (i-1 >= 0 && next_line != "") { // lower left
        char c = next_line[i-1];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i-1, length, next_line));
        }
    }
    if (next_line != "") { // lower center
        char c = next_line[i];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i, length, next_line));
        }
    }
    if (i+1 < length && next_line != "") { // lower right
        char c = next_line[i+1];
        if (std::isdigit(c)) {
            numbers.push_back(findNumber(i+1, length, next_line));
        }
    }
    std::cout << "found " << numbers.size() << " parts" << std::endl;
    return numbers;
}

int scanLines(std::string& prev_line, std::string& curr_line, std::string& next_line) {
    // modify numbers already found into .'s
    int sum = 0;
    for (size_t i = 0; i < curr_line.length(); ++i) {
        char c = curr_line[i];
        if (c == '*') {
            std::cout << "found *" << std::endl;
            std::vector<int> nums = getNumbers(i, curr_line.length(), prev_line, curr_line, next_line);
            if (nums.size() == 2) {
                sum += nums[0]*nums[1];
            }
        } else {
            continue;
        }
    }
    return sum;
}

int main() {
    std::string filename = "input.txt"; // Change this to your input file's name
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    int sum = 0;
    int line_num = 0;
    std::string prev_line = "";
    std::string curr_line = "";
    std::string next_line = "";
    while (std::getline(inputFile, line)) {
        // just store the previous and next line
        // if we are line = 1, it means we are on the first line
        // you look for symbols and see if there is any number surrounding them
        // then extract the number and store it in the sum
        prev_line = curr_line;
        curr_line = next_line;
        next_line = line;
        if (line_num == 0) {
            line_num += 1;
            continue;
        }
        std::cout << "processing line " << line_num << std::endl;
        int parts = scanLines(prev_line, curr_line, next_line); // scanLines can change the line
        sum += parts;
        line_num += 1;
    }
    // edge case for the end of the file - there is no "next line" any more
    prev_line = curr_line;
    curr_line = next_line;
    next_line = "";
    std::cout << "processing line " << line_num << std::endl;
    int parts = scanLines(prev_line, curr_line, next_line); // scanLines can change the line
    sum += parts;
    std::cout << "sum of game numbers is: " << sum << std::endl;
    inputFile.close();
    return 0;
}

	
