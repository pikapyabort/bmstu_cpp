#ifndef MESHLOADER_DATASTRUCTURES_H
#define MESHLOADER_DATASTRUCTURES_H
#include <utility>
#include <iostream>
#include <vector>

struct Node {
    int m_id = {0}; //ID узла
    std::vector<double> m_coordinates = {0, 0, 0}; //декартовы координаты узла
    bool m_vertex = {0}; //флаг, определяющий, является ли данный узел вершиной КЭ или его внутренним узлом.
    // 1 - vertex, 0 - inner element

    Node() = default;
    Node(const Node&) = default;
    Node(int, const std::vector<double> &, bool); //!!! Не хватает const у вектора
    //добавила

    friend std::ostream& operator<<(std::ostream&, const Node&);
    friend std::istream& operator>>(std::istream&, Node&);
};

struct Edge {
    std::pair<int, int> m_nodes;
    int m_mid = {-1};

    Edge() = default;
    Edge(int, int, int);

    bool operator==(const Edge&) const;
    friend std::ostream& operator<<(std::ostream&, const Edge&);
    friend std::istream& operator>>(std::istream&, Edge&);
};

struct FiniteElement {
    int m_id = {0}; // m_id_surface or m_id_material
    int m_id_var = {0};
    std::vector<int> m_nodes; //список ID узлов КЭ

    FiniteElement() = default;
    FiniteElement(int, std::vector<int>&);

    friend std::ostream& operator<<(std::ostream&, const FiniteElement&);
    friend std::istream& operator>>(std::istream&, FiniteElement&);
};

inline void hashCombine(std::size_t &o_seed, unsigned int &p_val) {
    o_seed ^= std::hash<unsigned int>()(p_val) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
}

inline std::size_t hashVal(const Edge &el) {
    std::size_t seed = 0;
    unsigned int a = std::min(el.m_nodes.first, el.m_nodes.second);
    unsigned int b = std::max(el.m_nodes.first, el.m_nodes.second);
    hashCombine(seed, a);
    hashCombine(seed, b);
    
    
    //!!! Для ребер (a,b) и (b,a) у вас получаются разные хеш-значения, хотя это одно ребра.
    //!!! Вершщины должны быть опорядочены.
    // так они же упорядочены – выбираем из пары минимум и максимум
    
    return seed;
}

class Hash {
public :
    std::size_t operator()(const Edge &p_c) const {
        return hashVal(p_c);
    }
};

#endif