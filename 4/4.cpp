#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <cmath>
#include <tuple>
#include <regex>
#include <cctype>

struct Card {
    int number;
    std::set<int> win;
    std::vector<int> drawn; // in case you can draw the same number twice...
};

Card parseCard(std::string& line) {
    Card card;
    std::regex pattern("Card \\s*(.*):\\s*(.*)\\|\\s*(.*)");
    std::smatch matches;
    if (std::regex_search(line, matches, pattern)) {
        if (matches.size() == 4) {
            std::string numberStr = matches[1].str();
            card.number = std::stoi(numberStr);
            std::string winStr = matches[2].str();
			std::istringstream winStream(winStr);
			int num;
			while (winStream >> num) {
				card.win.insert(num);
			}
            std::string drawStr = matches[3].str();
			std::istringstream drawStream(drawStr);
			while (drawStream >> num) {
				card.drawn.push_back(num);
			}
        } else {
            std::cerr << "error, bad regex match" << std::endl;
            exit(1);
        }
    } else {
            std::cerr << "error, bad regex match" << std::endl;
            exit(1);
    }
    return card;
}

int main() {
    std::string filename = "input.txt"; // Change this to your input file's name
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    int sum = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        Card card;
        card = parseCard(line);
		int count = 0;
		for (int d : card.drawn) {
            if (card.win.find(d) != card.win.end()) { 
                count += 1;
            }
		}
		std::cout << "card " << card.number << ": num wins: " << card.win.size() << ", num drawn: " << card.drawn.size() << ", matches: " << count << std::endl;
		if (count != 0) {
			sum += std::pow(2, count-1);
		}
    }
    std::cout << "sum of game numbers is: " << sum << std::endl;
    inputFile.close();
    return 0;
}

	
