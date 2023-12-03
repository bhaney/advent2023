#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <tuple>
#include <regex>
#include <cctype>

struct Game {
    int gameNumber;
    std::vector<std::map<std::string, int> > games;
};

std::tuple<int, std::string> extractGameNumber(const std::string& input) {
    std::regex pattern("Game (\\d+):\\s*(.*)");
    std::smatch matches;
    if (std::regex_search(input, matches, pattern)) {
        if (matches.size() == 3) {
            std::string numberStr = matches[1].str();
            int number = std::stoi(numberStr);
            std::string afterColon = matches[2].str();
            return std::make_tuple(number, afterColon);
	    }
    }
    return std::make_tuple(0, "");
}

std::map<std::string, int> processGameToken(std::string& input) {
    std::istringstream iss(input);
    std::string token;
    std::map<std::string, int> result;

    while (std::getline(iss, token, ',')) {
        std::regex pattern("(\\d+) \\s*(.*)");
        std::smatch matches;
        if (std::regex_search(token, matches, pattern)) {
            if (matches.size() == 3) {
                std::string numberStr = matches[1].str();
                int number = std::stoi(numberStr);
                std::string color = matches[2].str();
                result[color] = number;
            } else {
                std::cerr << "ERROR - could not parse number color phrase!" << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "ERROR - could not parse number color token!" << std::endl;
            exit(1);
        }
    }
    return result;
}

Game extractGame(const std::string& input) {
	Game game;
    int gameNumber;
    std::string restOfString;
    std::tie(gameNumber, restOfString) = extractGameNumber(input);
    if (gameNumber == 0) {
        std::cerr << "ERROR - could not parse string!" << std::endl;
        exit(1);
    }
    game.gameNumber = gameNumber;
    // a map of the colors, and game number
    std::istringstream iss(restOfString);
    std::string token;

    while (std::getline(iss, token, ';')) {
        std::map<std::string, int> result = processGameToken(token);
        game.games.push_back(result);
    }
	return game;

}

int gameProduct(const Game& game) {
    std::map<std::string, int> minimal_game;
    for (std::map<std::string, int> g : game.games) {
        // iterate through all colors in the game and create the power set
		std::map<std::string, int>::iterator it;
		for (it = g.begin(); it != g.end(); ++it) {
			const std::string& key = it->first;
			if (minimal_game[key]) {
                if (it->second > minimal_game[key]) {
                    minimal_game[key] = it->second;
                }
			} else {
                minimal_game[key] = it->second;
			}
		}
    }
    int product = 1;
	std::map<std::string, int>::iterator it;
    for (it = minimal_game.begin(); it != minimal_game.end(); ++it) {
        product *= it->second;
    }
    return product;
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
    while (std::getline(inputFile, line)) {
        Game game = extractGame(line);
        int product = gameProduct(game);
        std::cout << "product of game " << game.gameNumber << " is " << product << std::endl;
        sum += product;
    }
    std::cout << "sum of game numbers is: " << sum << std::endl;
    inputFile.close();
    return 0;
}

	
