#include "ViterbiEncoder.hpp"
#include <vector>


namespace viterbi {


bool ViterbiEncoder::get_output_value(int id, int mask, bool b) const {
    int formula = poly[id];

    int res = (formula & 1) ? b : 0;

    for (size_t i = 1; i < 32; ++i)
        if ((formula >> i) & 1)
            res ^= (mask >> (i - 1)) & 1;

    return res;
}
    
std::vector<bool> ViterbiEncoder::encode(const std::vector<bool>& data) const {
    std::vector<bool> code;
    code.reserve(data.size() * d);

    int mask = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        bool b = data[i];

        for (size_t out = 0; out < d; ++out)
            code.push_back(get_output_value(out, mask, b));

        mask = (mask << 1) + b;
    }

    return code;
}

}