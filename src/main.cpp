#include "ViterbiDecoder.hpp"
#include "ViterbiEncoder.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <random>
#include <fstream>


namespace {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<bool> generate_data(size_t n) {
        std::vector<bool> data(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = rd() % 2;
        return data;
    }

    std::vector<bool> noise_reduction(std::vector<bool> data, double p) {
        for (size_t i = 0; i < data.size(); ++i) {
            if (dis(gen) < p)
                data[i] = !data[i];
        }
        return data;
    }

}


int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "arguments error\n";
        exit(1);
    }
    
    double p = std::stod(argv[1]);

    int l = 2;

    std::vector<int> poly = {7, 5};

    viterbi::ViterbiEncoder ve(poly);
    viterbi::ViterbiDecoder vd(poly, l);


    size_t num_iterations = 100;
    size_t data_length = 1000;
    int total_errors = 0;
    size_t total_bits = 0;

    for (size_t iter = 0; iter < num_iterations; ++iter) {
        auto data = generate_data(data_length);
        auto code = ve.encode(data);
        auto noise_code = noise_reduction(code, p);
        auto decoded = vd.decode(noise_code);
        
        for (size_t i = 0; i < data.size(); ++i) {
            total_errors += (decoded[i] != data[i]);
        }
        total_bits += data.size();
    }

    double diff = static_cast<double>(total_errors) / total_bits;

    if (argc == 2)
        std::cout << diff << '\n';
    else {
        std::string filename = argv[2];
        std::ofstream in(filename);
        in << diff << '\n';
        in.close();
    }
}