#include <iostream>
#include <math.h>

int main() {
    //test set
    std::vector<uint64_t> test_time = {7,15, 30};
    std::vector<uint64_t> test_dist = {9, 40, 200};
    std::vector<uint64_t> test_time_2 = {71530};
    std::vector<uint64_t> test_dist_2 = {940200};
    // input set
    std::vector<uint64_t> input_time = {34, 90, 89, 86};
    std::vector<uint64_t> input_dist = {204, 1713, 1210, 1780};
    std::vector<uint64_t> input_time_2 = {34908986};
    std::vector<uint64_t> input_dist_2 = {204171312101780};

    std::vector<uint64_t> the_time = input_time_2;
    std::vector<uint64_t> the_dist = input_dist_2;
    uint product = 1;
    uint product2 = 1;
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
         std::cout << "count1: " << count << std::endl;
         product *= count;
         // ALTERNATIVE SOLUTION
        // can also just solve the quadratic equation in the condition: j(time-j) - thresh = 0
        // x^2 - x*time + dist = 0
        double x1 = (-double(time) + std::sqrt(double(time)*double(time) - 4*double(threshold))) / 2.;
        double x2 = (-double(time) - std::sqrt(double(time)*double(time) - 4*double(threshold))) / 2.;
         int count2 = int(x1)-int(x2);
         std::cout << "count2: " << count2 << std::endl;
         product2 *= count2;
         // ALTERNATIVE 2 -- use average speed?
         int count3 = 0;
         double total_time = double(time);
         double avg_speed_to_beat = double(threshold)/double(time);
         // calculate average speed of each possibility
         double avg_top_speed = (total_time/2.)*(total_time - total_time/2.)/total_time; 
        if (avg_top_speed > avg_speed_to_beat) {
            if(time%2 == 0) { // divides evenly, 1 max value}
                count3 += 1;
            } else {
                count3 += 2;
            }
         } else {
             continue;
         }
         for (uint j = time/2 + 1; j < time; j++) {
             double avg_speed = double(j)*(total_time - double(j))/total_time;
            if (avg_speed > avg_speed_to_beat) {
                count3 += 2;
            } else {
                break;
            }
         }
         std::cout << "count3: " << count3 << std::endl;
    }
    std::cout << "product1: " << product << std::endl;
    std::cout << "product2: " << product2 << std::endl;
}
