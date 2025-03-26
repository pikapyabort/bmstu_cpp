#include "MeshLoader.h"
#include "AneuMeshLoader.h"

//!!! Задание на защиту
//!!! Реализовать на основе std::ranges.
//!!! 1. Создать контейнер граничных элементов (треугольников)
//!!! 2. За один pipeline вывести в файл координаты вершин (вектор из 9 double)
//!!!    10 последних граничных КЭ, у которых площадь больше заданного значения.


std::vector<double> operator-(const std::vector<double>&a, const std::vector<double>&b) {
    if (a.size() != b.size())
        throw IncompitableDimException();
    std::vector<double> c;
    c.reserve(a.size());
    for(int i = 0; i < a.size(); ++i)
        c[i] = a[i] - b[i];
    return c;
}

namespace std {
    std::ostream &operator<<(std::ostream &ost, const std::vector<double> &vec) {
        for (double c: vec) {
            ost << c << " ";
        }
        ost << "\b";
        return ost;
    }
}

double triangleArea(const std::vector<double>&a, const std::vector<double>&b) {
    if (a.size() != b.size())
        throw IncompitableDimException();

    //i  j  k
    //a1 a2 a3
    //b1 b2 b3

    return sqrt(pow(a[0] * b[1] - a[1] * b[0], 2) +
                pow(a[0] * b[2] - a[2] * b[0], 2) +
                pow(a[1] * b[2] - a[2] * b[1], 2)) / 2;
}

double boundaryArea(const FiniteElement &el, const MeshLoader *loader) {
    auto A = loader->getNodes()[el.m_nodes[0]].m_coordinates;
    auto B = loader->getNodes()[el.m_nodes[1]].m_coordinates;
    auto C = loader->getNodes()[el.m_nodes[2]].m_coordinates;

    return triangleArea((A - B), (C - B));
}


int main(int argc, char *argv[]) {
    MeshLoader *loader = new AneuMeshLoader; //!!! Где delete?
    //исправила
    std::string s = "../cube.mesh";

    if (argc > 1) {
        loader->loadMesh(argv[0]);
    } else {
        loader->loadMesh(s);
    }

    auto boundaries = loader->getBoundaries();
    double area;


    std::cout << "Input max area: ";
    std::cin >> area;

    auto check = [&](const auto &elem) {
        return boundaryArea(elem, loader) < area;
    };

    auto result = boundaries | std::views::reverse | std::ranges::views::filter(check) |
                  std::ranges::views::take(10) | std::views::reverse |              //!!! Зачем нужен второй std::views::reverse?
                  std::ranges::views::transform([loader](const auto &element) {
                      return loader->getCoordinatesOfBoundaries(element);
                  });

    std::ofstream file("../defense.txt",std::ios::out);
    std::ranges::copy(result, std::ostream_iterator<std::vector<double>>(file, "\n"));

//    std::cout << std::endl << "Nodes: ";
//
//    for (auto elem : loader.getNodes())
//        std::cout << elem << "\n";
//    for (auto elem : loader.getFiniteElements())
//        std::cout << elem << "\n";
//    for (auto elem : loader.getBoundaries())
//        std::cout << elem << "\n";
//    std::cout << "find by vertices (2, 34, 38): \n";
//    for (auto elem : loader.findByVertices(2, 34, 38))
//        std::cout << elem << "\n";
//    std::cout << "find by edge (2, 34): \n";
//    for (auto elem : loader.findByEdge(2, 34))
//        std::cout << "elem id: "<< elem << "\n";
//
//    std::cout << "Nodes of volume 220: \n";
//    for (auto elem : loader.getNodesOfVolume(220))
//        std::cout << elem << "\n";
//
//    std::cout << "Nodes of surface 188: \n";
//    for (auto elem : loader.getBoundaryNodesByBoundaryId(188))
//        std::cout << elem << "\n";
//
//    std::cout << "Elements of material id = 1: ";
//    for (auto elem : loader.getElemsByMaterialId(1))
//        std::cout << elem << " ";
//    std::cout << "\n";
//
//    std::cout << "Boundary of surface id = 1: ";
//    for (auto elem : loader.getBoundariesBySurfaceId(1))
//        std::cout << elem << " ";
//    std::cout << "\n";
//
//

//    loader.insertNodesInMiddle();
//    std::cout << "The mesh after inserting new nodes in middles of edges:";
//    std::cout << std::endl << "Nodes: ";
//    for (auto elem : loader.getNodes())
//        std::cout << elem << "\n";
//    std::cout << std::endl << "Finite boundaries: ";
//    for (auto elem : loader.getFiniteElements())
//        std::cout << elem << "\n";
//    std::cout << std::endl << "Boundaries: ";
//    for (auto elem : loader.getBoundaries())
//        std::cout << elem << "\n";
//
//    std::cout << "The 18 node's neighbour:" << std::endl;
//    auto neighbours =  loader.getNeighbourNodes();
//    for (auto elem : neighbours[18])
//        std::cout << elem << " ";

    return 0;
}
