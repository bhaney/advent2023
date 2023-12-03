#include <iostream>
#include <fstream>
#include <map>
#include <cctype>


std::string extractNumberWord(const std::string& inputString, int p) {
	if (inputString.substr(p, 3) == "one") {
		return "1";
    } else if (inputString.substr(p, 3) == "two") {
        return "2";
    } else if (inputString.substr(p, 5) == "three") {
        return "3";
    } else if (inputString.substr(p, 4) == "four") {
        return "4";
    } else if (inputString.substr(p, 4) == "five") {
        return "5";
    } else if (inputString.substr(p, 3) == "six") {
        return "6";
    } else if (inputString.substr(p, 5) == "seven") {
        return "7";
    } else if (inputString.substr(p, 5) == "eight") {
        return "8";
    } else if (inputString.substr(p, 4) == "nine") {
        return "9";
    }
    return "";
}


std::vector<std::string> extractNumbers(const std::string& input) {
	std::vector<std::string> numbers;
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
		if (std::isdigit(c)) {
			char num = input[i] - '0';
			numbers.push_back(std::to_string(num));
		} else if ( c == 'o' || c == 't' || c == 'f' || c == 's' || c == 'e' || c == 'n') {
			std::string num = extractNumberWord(input, i);
			if (num != "") {
				numbers.push_back(num);
			}
		}
    }
	return numbers;
}

int main() {
    std::string filename = "input1.txt"; // Change this to your input file's name
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    int sum = 0;
    while (std::getline(inputFile, line)) {
        // Call the extractNumbers function for each line and get the extracted numbers
        std::vector<std::string> numbers = extractNumbers(line);
        // check if the vector is only  one number, if it is, double it
		if (numbers.size() == 0) {
			continue;
		}
		std::string num = "";
        if (numbers.size() == 1) {
			num = numbers[0] + numbers[0];
        } else {
			num = numbers.front() + numbers.back();
        }
		sum += std::stoi(num);
    	std::cout << "The number is: " << num << std::endl;
    }
    std::cout << "The sum is: " << sum << std::endl;

    inputFile.close();
    return 0;
}

	
