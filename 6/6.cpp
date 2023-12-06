#include <iostream>

int main() {
    //test set
    std::vector<int> test_time = {7,15, 30};
    std::vector<int> test_dist = {9, 40, 200};
    std::vector<int> test_time_2 = {71530};
    std::vector<int> test_dist_2 = {940200};
    // input set
    std::vector<int> input_time = {34, 90, 89, 86};
    std::vector<int> input_dist = {204, 1713, 1210, 1780};
    std::vector<uint64_t> input_time_2 = {34908986};
    std::vector<uint64_t> input_dist_2 = {204171312101780};

    std::vector<uint64_t> the_time = input_time_2;
    std::vector<uint64_t> the_dist = input_dist_2;
    uint product = 1;
    for (uint i = 0; i < the_time.size(); i++) {
        // divide each time in two as close as possible in two, then go down side, and double
        uint64_t count = 0;
        uint64_t time = the_time[i];
        uint64_t threshold = the_dist[i];
        uint64_t top_value = time / 2; // round down
        if (top_value*(time-top_value) > threshold) {
            if(time%2 == 0) { // divides evenly, 1 max value}
                count += 1;
            } else {
                count += 2;
            }
         } else {
             continue;
         }
         for (uint64_t j = top_value - 1; j > 0; j--) {
            if (j*(time-j) > threshold) {
                count += 2;
            } else {
                break;
            }
         }
         product *= count;
    }
    std::cout << "product " << product << std::endl;
}
