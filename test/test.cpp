#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ViterbiEncoder.hpp"
#include "ViterbiDecoder.hpp"


namespace viterbi {


void testing(size_t n, size_t l, size_t m) {
    srand(123);

    std::vector<int> poly(n);
    for (size_t i = 0; i < n; ++i)
        poly[i] = rand() % (1 << (l + 1));

    ViterbiEncoder ve(poly);


    std::vector<bool> _data(m);

    for (size_t i = 0; i < m; ++i)
        _data[i] = rand() % 2;

    auto code = ve.encode(_data);

    ViterbiDecoder vd(poly, l);

    auto predict_data = vd.decode(code);

    for (size_t i = 0; i < m; ++i) {
        // std::cout << _data[i] << " " << predict_data[i] << '\n';
        CHECK(predict_data[i] == _data[i]);
    }
}


TEST_CASE("Testing viterbi encoder/decoder") {

    SUBCASE("small test") {
        testing(2, 2, 5);
    }
    SUBCASE("big test") {
        testing(10, 4, 1000);
    }
}

}