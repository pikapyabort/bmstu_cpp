#pragma once
#include <iostream>
#include <algorithm>
#include <ranges>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <numeric>


//!!! Определения этих функций включаются в нескольких местах и вызывают ошибку линковки.
//!!! Дайте определения в cpp.
//исправила

void createDataByStreams(const std::string &filename, size_t num);
void createDataByAlgorithms(const std::string &filename, size_t num);

template<typename T>
T loadDataByStreams(const std::string& filename) {
    T container;
    std::ifstream in{filename};
    std::string line;

    if (!in) {
        std::cerr << "loadDataByStreams error: cannot open file" << std::endl;
        exit;
    }

    bool error = false;
    while (std::getline(in, line, ' ') && !error) {
        std::istringstream iss{line};
        typename T::value_type elem;
        if (!(iss >> elem))
            error = true;
        else
            container.push_back(elem);
    }

    return container;
}

template<typename T>
T loadDataAlgorithms(const std::string &filename) {
    T container{};
    std::ifstream in{filename};

    if (!in) {
        std::cerr << "loadDataAlgorithms error: cannot open file" << std::endl;
        exit;
    } else {
        std::copy(std::istream_iterator<typename T::value_type>(in),
                  std::istream_iterator<typename T::value_type>(), std::back_inserter(container));
    }
    return container;
}

//template <typename T>
//void outputResultByCout(const T &cont) {
//    for (const auto& elem : cont)
//        std::cout << elem << ' ';
//    std::cout << std::endl;
//}

template <typename T>
void outputResultByStreams(const std::string &filename, const T &cont) {
    std::ofstream out(filename, std::ios::app);
    for (const auto& elem : cont)
        out << elem << ' ';
    out << std::endl;
}

template <typename T>
void outputResultAlgorithms(const std::string &filename, const T& cont) {
    std::ofstream out(filename, std::ios::app);
    std::copy(cont.begin(), cont.end(), std::ostream_iterator<typename T::value_type>(out, " "));
    out << std::endl;
}

template<typename iter>
typename iter::value_type max(iter begin, iter end) {
    return *std::max_element(begin, end);
}

//modify = subtract the maximum from each element
template<typename Container>
Container modifyTemplate(Container &cont) {
    auto max = *std::max_element(cont.begin(), cont.end());
    for (auto &it : cont) {
        it -= max;
    }
    auto sum = std::accumulate(cont.begin(), cont.end(), 0);
    auto avg = sum / cont.size();
    avg = std::abs(static_cast<int>(avg));
    cont.push_back(sum);
    cont.push_back(avg);
    return cont;
}

template<typename InputIt>
void modifyIter(InputIt beg, InputIt end) {
    auto max = *std::max_element(beg, end);
    for (auto it = beg; it != end; ++it) {
        *it -= max;
    }
}

template<typename InputIt>
void modifyForEach(InputIt beg, InputIt end) {
    auto modify = [&beg, &end](typename std::iterator_traits<InputIt>::value_type &elem) {
        auto max = std::abs(static_cast<int>(*std::max_element(beg, end)));
        elem -= max;
    };
    std::for_each(beg, end, modify);
}

template <typename T>
void outputResultByCout(const T &cont) {
    for (const auto& elem : cont)
        std::cout << elem << ' ';
    std::cout << std::endl;
}

template<typename T>
void modifyTransform(const std::string &nameIn, const std::string &nameOut) {
    std::ifstream in(nameIn);
    std::ofstream out(nameOut);

    auto max = *std::max_element(std::istream_iterator<T>(in), std::istream_iterator<T>());

    in.clear();
    in.seekg(0, std::ios::beg);

    std::transform(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::ostream_iterator<T>(out, " "),
            [max](const auto& elem) { return elem - max; });

    out << std::endl;
}
