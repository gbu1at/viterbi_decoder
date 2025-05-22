#pragma once
#include <vector>

namespace viterbi {

class ViterbiDecoder {
private:
    std::vector<int> poly;
    size_t d;
    size_t l;

    int distance(const std::vector<bool>&, const std::vector<bool>&) const;

    std::vector<bool> get_output_value(int, bool) const;

public:
    ViterbiDecoder() = delete;
    
    ViterbiDecoder(const std::vector<int>& poly, size_t l) : 
        poly(poly), d(poly.size()), l(l) {
        
    }
    std::vector<bool> decode(const std::vector<bool>&) const;

};

}