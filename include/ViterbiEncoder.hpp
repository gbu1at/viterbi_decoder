#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>


namespace viterbi {


class ViterbiEncoder {

private:
    std::vector<int> poly;
    size_t d;
    
    bool get_output_value(int, int, bool) const;

public:    
    ViterbiEncoder(const std::vector<int>& poly) : 
        poly(poly), d(poly.size()) {
    }

    std::vector<bool> encode(const std::vector<bool>&) const;
};

}