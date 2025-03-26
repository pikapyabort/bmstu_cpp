#include "data.h"

void createDataByStreams(const std::string &filename, size_t num) {
    std::ofstream out(filename);
    for (int i = 0; i < num-1; ++i)
        out << -50 + rand() % 101 << ' ';
    out << -50 + rand() % 101;
    out << std::endl;
}

void createDataByAlgorithms(const std::string &filename, size_t num) {
    std::vector<int> myvec(num);
    std::generate(myvec.begin(), myvec.end(), []() { return -50 + rand() % 101; });

    std::ofstream out(filename, std::ios::app);
    std::ostream_iterator<int> out_it(out, " ");
    std::copy(myvec.begin(), myvec.end() - 1, out_it);
    out << *(myvec.end() - 1) << std::endl;
}
