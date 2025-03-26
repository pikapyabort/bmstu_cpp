#include "MeshLoader.h"

//!!! Задание на защиту (не удалять)
//!!! Реализовать на основе std::ranges.
//!!! 1. Создать контейнер граничных элементов (треугольников)
//!!! 2. За один pipeline вывести в файл координаты вершин (вектор из 9 double) 
//!!!    10 последних граничных КЭ, у которых площадь больше заданного значения.




//!!! Почему эти методы возвращают по значению и копируют кучу данных?
// теперь возвращают по константной ссылке

const std::vector<Node> &MeshLoader::getNodes() const {
    return m_nodes;
}

const std::vector<FiniteElement> &MeshLoader::getFiniteElements() const {
    return m_elems;
}

const std::vector<FiniteElement> &MeshLoader::getBoundaries() const {
    return m_boundaries;
}

//метод, позволяющий найти КЭ по ID трех его вершинных узлов, для чего использовать алгоритм find_if и создать необходимый предикат.
std::vector<int> findIf(const std::vector<FiniteElement> &p_elems, const std::function<bool(const FiniteElement &)> &pred) {
    auto beg = p_elems.begin(), end = p_elems.end();
    std::vector<int> result;
    int index = 0;
    while(beg != end) {
        beg = std::find_if(beg, end, pred);
        if (beg != end) {
            result.push_back(index);
            ++beg;
        }
        ++index;
    }
    return result;
}

std::vector<int> MeshLoader::findByVertices(int p_id1, int p_id2, int p_id3) const {
    return findIf(m_elems, [p_id1, p_id2, p_id3](const FiniteElement &elem) {
        auto beg = elem.m_nodes.begin(), end = elem.m_nodes.end();
        //!!! Используйте std::any_of
        //использовала

        return std::any_of(beg, end, [&](unsigned int i){ return i == p_id1; }) &&
               std::any_of(beg, end, [&](unsigned int i){ return i == p_id2; }) &&
               std::any_of(beg, end, [&](unsigned int i){ return i == p_id3; });
    });
}

//	метод, позволяющий найти КЭ по ребру, заданному с помощью ID двух узлов
std::vector<int> MeshLoader::findByEdge(int p_id1, int p_id2) const {
    return findIf(m_elems, [p_id1, p_id2](const FiniteElement &elem) {
        auto beg = elem.m_nodes.begin(), end = elem.m_nodes.end();
        return find(beg, end, p_id1) != end && find(beg, end, p_id2) != end;
    });
}


///getters
std::unordered_set<int> MeshLoader::getNodesOfVolume(int p_id) const {
    if(p_id >= m_elems.size())
        throw "id of volume is too big!";

    std::unordered_set<int> result;

    for(auto x : m_elems[p_id].m_nodes) //by index?
        result.insert(x);

    return result;
}

std::unordered_set<int> MeshLoader::getBoundaryNodesByBoundaryId(int p_id) const {
    if(p_id >= m_boundaries.size())
        throw "id of surface is too big!";

    std::unordered_set<int> result;

    for(auto x : m_boundaries[p_id].m_nodes)
        result.insert(x);

    return result;
}


std::vector<int> MeshLoader::getElemsByMaterialId(int material_id) const {
    return findIf(m_elems, [material_id](const FiniteElement &elem) {
        return elem.m_id_var == material_id; });
}

std::vector<int> MeshLoader::getBoundariesBySurfaceId(int surface_id) const {
    return findIf(m_boundaries, [surface_id](const FiniteElement &elem) {
        return elem.m_id_var == surface_id; });
}

void MeshLoader::insertNodesInMiddle() {
    std::unordered_set<Edge, Hash> edges;
    size_t dim_el =  m_elems[0].m_nodes.size(), dim_b = m_boundaries[0].m_nodes.size();

    for (auto &elem: m_elems) {
        for (int i = 0; i < dim_el; ++i) {
            for (int j = i + 1; j < dim_el; ++j) {
                Edge edge(elem.m_nodes[i], elem.m_nodes[j], 0);
                auto [iter, res] = edges.insert(edge);
                if (res) {
                    Node node = createMiddleNode(edge);
                    edge.m_mid = node.m_id;
                    elem.m_nodes.push_back(node.m_id);
                    m_nodes.push_back(std::move(node));
                } else {
                    elem.m_nodes.push_back(iter->m_mid);
                }
            }
        }
    }

    for (auto &boundary: m_boundaries) {
        dim_b = boundary.m_nodes.size();
        for (int i = 0; i < dim_b; ++i) {
            for (int j = i + 1; j < dim_b; ++j) {
                Edge edge(boundary.m_nodes[i], boundary.m_nodes[j], 0);
                auto iter = edges.find(edge);
                if (iter != edges.end())
                    boundary.m_nodes.push_back(iter->m_mid);
                else {
                    edges.insert(edge);
                    Node node = createMiddleNode(edge);
                    edge.m_mid = node.m_id;
                    boundary.m_nodes.push_back(node.m_id);
                    m_nodes.push_back(std::move(node));
                }
            }
        }
    }
}

Node MeshLoader::createMiddleNode(const Edge &edge) {
    std::vector<double> coord(3);
    coord[0] = (m_nodes[edge.m_nodes.first].m_coordinates[0] + m_nodes[edge.m_nodes.second].m_coordinates[0]) / 2;
    coord[1] = (m_nodes[edge.m_nodes.first].m_coordinates[1] + m_nodes[edge.m_nodes.second].m_coordinates[1]) / 2;
    coord[2] = (m_nodes[edge.m_nodes.first].m_coordinates[2] + m_nodes[edge.m_nodes.second].m_coordinates[2]) / 2;
    Node node{(int)m_nodes.size() + 1, coord, false};
    return node;
}



std::unordered_map<int, std::unordered_set<int>> MeshLoader::getNeighbourNodes() const {
    std::unordered_map<int, std::unordered_set<int>> result;
    auto getRelations = [&result](const FiniteElement &elem) {
        for(auto i : elem.m_nodes)
            for(auto j : elem.m_nodes)
                if(i != j)
                    result[i].insert(j);
    };
    for_each(m_elems.begin(), m_elems.end(), getRelations);
    return result;
}

std::vector<double> MeshLoader::getCoordinatesOfBoundaries(const FiniteElement &p_boundary) const {
    std::vector<double> result;
    for (const auto id: p_boundary.m_nodes) {
        for (double c: m_nodes[id].m_coordinates) {
            result.push_back(c);
        }
    }
    return result;
}
