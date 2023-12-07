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

std::map<char, int> cardMap {
    {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5},
        {'7', 6}, {'8', 7}, {'9', 8}, {'T',9}, {'J',0}, {'Q',11}, {'K', 12}, {'A', 13},
};

struct Hand {
    std::string raw;
    std::string desc;
    std::vector<int> cards;
    int strength;
    int bid;

    void convertHand() {
        // take the raw string and find out its strength
        if (raw.size() < 5) {
            std::cerr << "did not initialize hand" << std::endl;
            exit(1);
        }
        cards.clear();
        std::map<char, int> myMap;
        for (char c: raw) {
            cards.push_back(cardMap[c]);
            if (myMap.count(c)) {
                myMap[c] += 1;
            } else {
                myMap[c] = 1;
            }
        }
        if (myMap.count('J')) {
            strengthWithJoker(myMap);
        } else {
            strengthWithoutJoker(myMap);
        }
    }

    void strengthWithJoker(const std::map<char, int> myMap) {
        strength = 1;
        desc = "high card";
        bool has_two = false;
        bool has_two_two = false;
        bool has_three = false;
        bool has_four = false;
        for (const auto& pair : myMap) {
            if (pair.first == 'J') {
                continue;
            }
            if (has_two && pair.second == 2) {
                has_two_two = true;
            }
            if (pair.second == 2) {
                has_two = true;
            }
            if (pair.second == 3) {
                has_three = true;
            }
            if (pair.second == 4) {
                has_four = true;
            }
        } 
        if (myMap.at('J') == 5 || myMap.at('J') == 4) {
            strength = 7;
            desc = "five of a kind";
            return;
        }
        if (myMap.at('J') == 3) {
            if(has_two) {
                strength = 7;
                desc = "five of a kind";
                return;
            }
            strength = 6;
            desc = "four of a kind";
            return;
        }
        if (myMap.at('J') == 2) {
            if(has_three) {
                strength = 7;
                desc = "five of a kind";
                return;
            }
            if(has_two) {
                strength = 6;
                desc = "four of a kind";
                return;
            }
            strength = 4;
            desc = "three of a kind";
            return;
        }
        if(has_four) {
            strength = 7;
            desc = "five of a kind";
            return;
        }
        if(has_three) {
            strength = 6;
            desc = "four of a kind";
            return;
        }
        if(has_two_two) {
            strength = 5;
            desc = "full house";
            return;
        }
        if(has_two) {
            strength = 4;
            desc = "three of a kind";
            return;
        }
        strength = 2;
        desc = "one pair";
        return;
    }

    void strengthWithoutJoker(const std::map<char, int> myMap) {
        strength = 1;
        desc = "high card";
        bool has_two = false;
        bool has_three = false;
        for (const auto& pair : myMap) {
            if (has_two && pair.second == 2) {
                strength = 3;
                desc = "two pair";
                break;
            }
            if (pair.second == 2) {
                has_two = true;
            }
            if (pair.second == 3) {
                has_three = true;
            }
            // calculate strengths
            if (pair.second == 5) {
                strength = 7;
                desc = "five of a kind";
                break;
            }
            if (pair.second == 4) {
                strength = 6;
                desc = "four of a kind";
                break;
            }
            if ((pair.second == 3 && has_two) || pair.second == 2 && has_three) {
                strength = 5;
                desc = "full house";
                break;
            }
            if (has_three && !has_two) {
                strength = 4; // might still be a full house later
                desc = "three of a kind";
                continue;
            }
            if (has_two) {
                strength = 2;
                desc = "one pair";
            }
        } 
        return;
    }
};

bool compareHands(const Hand& a, const Hand& b) {
    if (a.strength == b.strength) {
        for(int i = 0; i < 5; i++) {
            if (a.cards[i] == b.cards[i]) {
                continue;
            }
            return a.cards[i] < b.cards[i];
        }
    }
    return a.strength < b.strength;
}


int main() {
    std::string filename = "input.txt"; // Change this to your input file's name
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Hand> hands;
    while (std::getline(inputFile, line)) {
        Hand hand;
        std::istringstream handStream(line);
        handStream >> hand.raw;
        handStream >> hand.bid;
        hand.convertHand();
        std::cout << "hand " << hand.raw <<  " is " << hand.desc << "(" << hand.strength << ")" << std::endl;
        hands.push_back(hand);
    }
    uint64_t sum = 0;
    std::sort(hands.begin(), hands.end(), compareHands);
    for (int i = 0; i < hands.size(); i++) {
        sum += (i+1)*hands[i].bid;
    }
    std::cout << "sum is: " << sum << std::endl;
    inputFile.close();
    return 0;
}

	
