#include "viterbi_encode.hpp"
#include "viterbi_decode.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>



std::vector<bool> generate_data(size_t n) {
    std::vector<bool> data(n);
    for (size_t i = 0; i < n; ++i)
        data[i] = rand() % 2;
    return data;
}

std::vector<bool> noise_reduction(std::vector<bool> data, double p) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (rand() / (double)RAND_MAX < p)
            data[i] = !data[i];
    }
    return data;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "arguments error\n";
        exit(1);
    }
    
    double p = std::stod(argv[1]);
    
    int l = 3;

    std::vector<int> poly = {7, 3, 14, 2};

    viterbi::ViterbiEncoder ve(poly);

    size_t n = 100;

    auto data = generate_data(n);
    auto code = ve.encode(data);
    auto noise_code = noise_reduction(code, p);

    viterbi::ViterbiDecoder vd(poly, l);
    auto decode_noise_code = vd.decode(noise_code);

    int diff = 0;

    for (size_t i = 0; i < n; ++i)
        diff += (decode_noise_code[i] != data[i]);
    
    std::cout << diff << '\n';

}