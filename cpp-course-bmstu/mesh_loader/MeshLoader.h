#ifndef MESHLOADER_MESHLOADER_H
#define MESHLOADER_MESHLOADER_H
#include "DataStructures.h"
#include "Exception.h"
#include <unordered_set>
#include <set>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <ranges>
#include <cmath>

class MeshLoader {
protected:
    std::vector<Node> m_nodes;
    std::vector<FiniteElement> m_elems;
    std::vector<FiniteElement> m_boundaries;
public:

    virtual void loadMesh(const std::string&) = 0;

    virtual ~MeshLoader() = default;

    //методы, позволяющие получить STL-контейнеры узлов, конечных элементов и граничных элементов
    
    //!!! Зачем делать эти методы виртуальными?
    // не знаю. исправила.
    
    const std::vector<Node> &getNodes() const;
    const std::vector<FiniteElement> &getFiniteElements() const;
    const std::vector<FiniteElement> &getBoundaries() const;


    //метод, позволяющий найти КЭ по ID трех его вершинных узлов, для чего использовать алгоритм find_if
    //и создать необходимый предикат.
    [[nodiscard]] std::vector<int> findByVertices(int, int, int) const;
    //метод, позволяющий найти КЭ по ребру, заданному с помощью ID двух узлов.
    [[nodiscard]] std::vector<int> findByEdge(int, int) const;

    std::unordered_set<int> getNodesOfVolume(int p_id) const;
    std::unordered_set<int> getBoundaryNodesByBoundaryId(int p_id) const; //surface == boundary
    std::vector<int> getElemsByMaterialId(int material_id) const;
    std::vector<int> getBoundariesBySurfaceId(int surface_id) const;




//    метод, производящий вставку новых узлов в середины ребер существующих КЭ (включая граничные КЭ). Учесть, что обновляются как списки узлов каждого КЭ, так общий список узлов сетки;
//    метод, создающий контейнер, n-ый элемент которого хранит контейнер всех «соседей» по ребрам для узла n;
//    методы, реализующие отформатированный вывод Node и FiniteElement в заданный поток;
//    при необходимости возможно определение других методов и типов данных.

    void insertNodesInMiddle();
    Node createMiddleNode(const Edge &edge);
    std::unordered_map<int, std::unordered_set<int>> getNeighbourNodes() const;
    std::vector<double> getCoordinatesOfBoundaries(const FiniteElement &p_boundary) const;

    //defense
    double boundaryArea(const FiniteElement &el, const MeshLoader *loader);

};

#endif
