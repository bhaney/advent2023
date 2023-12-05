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

struct Problem {
    std::vector<uint> seeds;
    std::function<uint(uint)> seed_to_soil;
    std::function<uint(uint)> soil_to_fertilizer;
    std::function<uint(uint)> fertilizer_to_water;
    std::function<uint(uint)> water_to_light;
    std::function<uint(uint)> light_to_temp;
    std::function<uint(uint)> temp_to_humidity;
    std::function<uint(uint)> humidity_to_location;
};

struct Triple {
    uint destinationStart;
    uint sourceStart;
    uint range;
};

std::function<uint(uint)> parseTriplesToMapper(std::vector<Triple> triples) {
    std::vector<Triple> funcTriples = triples;
    return [funcTriples](uint input) -> uint {
        // check if input is within the source range at all
        for (Triple t : funcTriples) {
            if (input >= t.sourceStart && input < t.sourceStart + t.range) {
                uint displacement = input - t.sourceStart;
                uint output = t.destinationStart + displacement;
                std::cout << "  source " << input << " is between " << t.sourceStart << " and " << t.sourceStart + t.range << " and will have output " << output << std::endl;
                return output;
            }
        }
        std::cout << "  source " << input << " will have output " << input << std::endl;
        return input;
    };
}

int main() {
    std::string filename = "input.txt"; // Change this to your input file's name
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<Triple> storage;
    std::string state = "PARSING";
    Problem problem;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << "in state " << state << " with line " << line << std::endl;
        if (state == "PARSING") {
            if( line == "") {
                continue;
            }
            if(line.find("seeds:") != std::string::npos) {
                state = "SEEDS";
            } else if (line.find("seed-to-soil") != std::string::npos) {
                state = "SEED_MAP";
                continue;
            } else if (line.find("soil-to-fert") != std::string::npos) {
                state = "SOIL_MAP";
                continue;
            } else if (line.find("fertilizer-to-water") != std::string::npos) {
                state = "FERT_MAP";
                continue;
            } else if (line.find("water-to-light") != std::string::npos) {
                state = "WATER_MAP";
                continue;
            } else if (line.find("light-to-temp") != std::string::npos) {
                state = "LIGHT_MAP";
                continue;
            } else if (line.find("temperature-to-humid") != std::string::npos) {
                state = "TEMP_MAP";
                continue;
            } else if (line.find("humidity-to-loc") != std::string::npos) {
                state = "HUMID_MAP";
                continue;
            } else {
                std::cerr << "cant parse line " << line << std::endl;
                exit(1);
            }
        }
        if ( state == "SEEDS") {
            std::cout << "parsing seeds line " << line << std::endl;
            std::string seeds = line.substr(6); // skip past "seeds:"
            uint num;
            std::istringstream seedStream(seeds);
            while(seedStream >> num) {
                std::cout << "seed : " << num << std::endl;
                problem.seeds.push_back(num);
            }
            state = "PARSING";
            continue;
        }
        if ( state == "SEED_MAP" && line == "") {
            problem.seed_to_soil = parseTriplesToMapper(storage);
            storage.clear();
            state = "PARSING";
            continue;
        }
        if ( state == "SOIL_MAP" && line == "") {
            problem.soil_to_fertilizer = parseTriplesToMapper(storage);
            storage.clear();
            state = "PARSING";
            continue;
        }
        if ( state == "FERT_MAP" && line == "") {
            problem.fertilizer_to_water = parseTriplesToMapper(storage);
            storage.clear();
            state = "PARSING";
            continue;
        }
        if ( state == "WATER_MAP" && line == "") {
            problem.water_to_light = parseTriplesToMapper(storage);
            storage.clear();
            state = "PARSING";
            continue;
        }
        if ( state == "LIGHT_MAP" && line == "") {
            problem.light_to_temp = parseTriplesToMapper(storage);
            storage.clear();
            state = "PARSING";
            continue;
        }
        if ( state == "TEMP_MAP" && line == "") {
            problem.temp_to_humidity = parseTriplesToMapper(storage);
            storage.clear();
            state = "PARSING";
            continue;
        }
        if ( state == "HUMID_MAP" && line == "") {
            problem.humidity_to_location = parseTriplesToMapper(storage);
            storage.clear();
            state = "PARSING";
            continue;
        }
        Triple triple;
        std::istringstream stream(line);
        stream >> triple.destinationStart;
        std::cout << "  destination start is " << triple.destinationStart << std::endl;
        stream >> triple.sourceStart;
        std::cout << "  source start is " << triple.sourceStart << std::endl;
        stream >> triple.range;
        std::cout << "  range start is " << triple.range << std::endl;
        storage.push_back(triple);
        
    }
    // once the problem is set up, then actuall solve it
    uint least = std::numeric_limits<uint>::max();
    for (uint seed : problem.seeds) {
        std::cout << "initial seed " << seed << std::endl;
        uint soil = problem.seed_to_soil(seed);
        uint fert = problem.soil_to_fertilizer(soil);
        uint water = problem.fertilizer_to_water(fert);
        uint light = problem.water_to_light(water);
        uint temp = problem.light_to_temp(light);
        uint humid = problem.temp_to_humidity(temp);
        uint location = problem.humidity_to_location(humid);
        if (location < least) {
            least = location;
        }
    }
    std::cout << "least of game numbers is: " << least << std::endl;
    inputFile.close();
    return 0;
}

	
