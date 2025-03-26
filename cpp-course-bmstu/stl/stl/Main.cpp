#include "Container.h"
#include "Algorithms.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <ranges>

struct Goods {
    uint32_t m_id;
    std::string m_name;
    std::string m_manufacturer;
    std::string m_warehouse_address;
    double m_weight;

    Goods() noexcept :
            m_id(0),
            m_name(""),
            m_manufacturer(""),
            m_warehouse_address(""),
            m_weight(0.) {}

    Goods(uint32_t id, const std::string& name, const std::string& manufacturer, const std::string& warehouse_address, double weight) :
            m_id(id),
            m_name(name),
            m_manufacturer(manufacturer),
            m_warehouse_address(warehouse_address),
            m_weight(weight) {}


    bool operator<(const Goods& r) const {
        return m_name < r.m_name;
    }

};

class func {
public:
    auto operator()(const Goods& goods) {
        return goods.m_manufacturer == "Nevskaya palitra";
    }
};

void PrintHeader() {
    std::cout << "+-----+----------------+-----------------+--------------+--------+" << std::endl;
    std::cout << "| ID  | Name           | Manufacturer    | Adress       | Weight |" << std::endl;
    std::cout << "+-----+----------------+-----------------+--------------+--------+" << std::endl;
}


int main() {
    std::cout << "|----------------------------Task#2------------------------------|" << std::endl;
    Vector<Goods> cont_1{ { 1, "black", "Nevskaya palitra", "USA", 0.5},
                          { 2, "orange", "White nights", "Russia", 0.9 },
                          { 3, "green", "Pebeo", "Germany", 0.2 } };
    std::cout << "cont_1" << std::endl;

    PrintHeader();

    auto print = [](const Goods& good) {
        std::cout << "|" << std::setw(5) << std::left << good.m_id;
        std::cout << "|" << std::setw(16) << std::left << good.m_name;
        std::cout << "|" << std::setw(17) << std::left << good.m_manufacturer;
        std::cout << "|" << std::setw(14) << std::left << good.m_warehouse_address;
        std::cout << "|" << std::setw(8) << std::left << good.m_weight << "|" << std::endl;
        std::cout << "+-----+----------------+-----------------+--------------+--------+" << std::endl;
    };

    forEach(cont_1.begin(), cont_1.end(), print);

    std::cout << "|----------------------------Task#3------------------------------|" << std::endl;
    Goods g1{ 4, "white", "Gamma", "Australia", 1 };
    Goods g2{ 5, "yellow", "Van Gogh", "USA", 1.2 };
    Goods g3{ 6, "blue", "White nights", "Austria", 1 };
    Goods g4{ 7, "red", "Pebeo", "France", 0.7 };

    Vector<Goods> cont_2;

    cont_2.pushBack(g1);
    cont_2.pushBack(g2);
    cont_2.pushBack(g3);
    cont_2.emplace_back(8, "purple", "Nevskaya palitra", "USA", 1.2);

    cont_2.insert(cont_2.begin(), g4);

    std::cout << "cont_2" << std::endl;
    PrintHeader();
    forEach(cont_2.begin(), cont_2.end(), print);

    std::cout << "|----------------------------Task#3------------------------------|" << std::endl;

    VectorIterator<Goods> iterb = cont_1.begin();
    cont_1.insert(iterb + 2, cont_2.begin(), cont_2.end());
    std::cout << "cont_1" << std::endl;
    PrintHeader();
    forEach(cont_1.begin(), cont_1.end(), print);

    std::cout << "|----------------------------Task#4------------------------------|" << std::endl;
    Sort(cont_1.begin(), cont_1.end());
    std::cout << "cont_1" << std::endl;
    PrintHeader();
    forEach(cont_1.begin(), cont_1.end(), print);

    std::cout << "|----------------------------Task#5------------------------------|" << std::endl;
    std::cout << "cont_1" << std::endl;
    PrintHeader();
    forEach(cont_1.begin(), cont_1.end(), print);

    auto RangeWeight = [](const auto& s) {
        return (1 < s.m_weight) && (s.m_weight < 5);
    };

    auto res = findIf(cont_1.begin(), cont_1.end(), RangeWeight);
    std::cout << std::endl << "search result: " << std::endl;
    PrintHeader();
    print(*res);

    std::cout << "|----------------------------Task#6------------------------------|" << std::endl;

    res->m_warehouse_address = "USA";
    std::cout << "cont_1" << std::endl;
    PrintHeader();
    forEach(cont_1.begin(), cont_1.end(), print);

    std::cout << "|----------------------------Task#7------------------------------|" << std::endl;
    func f;
    Vector<Goods> cont_3(2);
    copyIf(cont_1.begin(), cont_1.end(), cont_3.begin(),
           func());
    std::cout << "cont_3" << std::endl;
    PrintHeader();
    forEach(cont_3.begin(), cont_3.end(), print);
}