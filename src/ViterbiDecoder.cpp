#include "ViterbiDecoder.hpp"

#include <stdexcept>
#include <vector>
#include <algorithm>


namespace viterbi {

const int INF = 1e9;

int ViterbiDecoder::distance(const std::vector<bool>& x, const std::vector<bool>& y) const {
    int dist = 0;
    for (size_t i = 0; i < d; ++i)
        dist += (x[i] != y[i]);
    return dist;
}

std::vector<bool> ViterbiDecoder::get_output_value(int mask, bool b) const {
    std::vector<bool> res(d);
    for (size_t i = 0; i < d; ++i) {
        int formula = poly[i];
        res[i] = ((formula & 1) ? b : 0);

        for (size_t j = 1; j < 32; ++j)
            if ((formula >> j) & 1)
                res[i] = res[i] ^ ((mask >> (j - 1)) & 1);
    }
    return res;
}
    

std::vector<bool> ViterbiDecoder::decode(const std::vector<bool>& code) const {
    if (code.size() % d != 0)
        throw std::runtime_error("code must be equal zero mod d");

    size_t blocks = code.size() / d;
    std::vector<int> dp((1 << l), INF);
    std::vector<int> nextdp((1 << l), INF);

    std::vector<std::vector<std::pair<int, int> >> links(blocks, std::vector<std::pair<int, int>>(1 << l, {-1, -1}));

    dp[0] = 0;

    for (size_t block = 0; block < blocks; ++block) {
        nextdp.assign((1 << l), INF);

        std::vector<bool> code_value(d);
        for (size_t i = 0; i < d; ++i)
            code_value[i] = code[block * d + i];
        
        for (int mask = 0; mask < (1 << l); ++mask) {
            for (auto b : {0, 1}) {
                int next_mask = ((mask << 1) | b) & ((1 << l) - 1);

                std::vector<bool> prdeict_value = get_output_value(mask, b);
                int dist = distance(prdeict_value, code_value);

                
                if (nextdp[next_mask] > dp[mask] + dist) {
                    

                    nextdp[next_mask] = dp[mask] + dist;
                    links[block][next_mask] = {mask, b};
                }
            }
        }
        swap(dp, nextdp);
    }

    int nearest_mask = 0;
    for (int mask = 0; mask < (1 << l); ++mask) {
        if (dp[nearest_mask] > dp[mask])
            nearest_mask = mask;
    }


    std::vector<bool> data;
    data.reserve(blocks);

    for (int block = blocks - 1; block >= 0; --block) {
        data.push_back(links[block][nearest_mask].second);
        nearest_mask = links[block][nearest_mask].first;
    }

    std::reverse(data.begin(), data.end());

    return data;
}


}