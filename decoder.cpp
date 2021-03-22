#include "discrete_val.h"
#include <vector>
#include <iostream>
#include <cmath>

// check matrix 4/6
std::vector<std::vector<int>> H = {
    {1, 1, 0, 1, 0, 0},
    {0, 1, 1, 0, 1, 0},
    {1, 0, 0, 0, 1, 1},
    {0, 0, 1, 1, 0, 1}
    };


// channel probability
float CHANNEL_PROB = 0.2;

// size of the input message
size_t MESSAGE_SIZE = 6;


// make llr out of input message
std::vector<float> make_input_llr(std::vector<int> input) {
    std::vector<float> r = std::vector<float>(MESSAGE_SIZE, 0);
    for (size_t i = 0; i < r.size(); ++i) {
        r[i] = log(CHANNEL_PROB/(1 - CHANNEL_PROB));
        if (input[i] == 0) {
            r[i] = -r[i];
        }
    }
    return r;
}

std::vector<std::vector<float>> E = std::vector<std::vector<float>>(4, std::vector<float>(6, 0));
std::vector<std::vector<float>> M = std::vector<std::vector<float>>(4, std::vector<float>(6, 0));

void make_M(std::vector<std::vector<float>> & M, std::vector<std::vector<float>> E, std::vector<float> r) {
    
}

void make_E(std::vector<std::vector<float>> M, std::vector<std::vector<float>> & E, std::vector<float> r) {
    
}


int main() {
    std::vector<int> input = {1, 0, 1, 0, 1, 1};
    std::vector<float> r = make_input_llr(input);
    for (size_t i = 0; i < r.size(); ++i) {
        std::cout << r[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
