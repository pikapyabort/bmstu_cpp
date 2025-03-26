#include "AneuMeshLoader.h"


void AneuMeshLoader::loadMesh(const std::string &p_filename) {
    std::ifstream f_in(p_filename);

    if (!f_in) {
        throw FileNotFoundException();
    }
    else {
        std::cout << "File " << p_filename << " was opened successfully!" << std::endl;
    }

    int amount, dim;
    f_in >> amount >> dim;
    m_nodes.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        Node tmp;
        f_in >> tmp.m_coordinates[0] >> tmp.m_coordinates[1] >> tmp.m_coordinates[2];
        tmp.m_id = i;
        tmp.m_vertex = true;
        m_nodes.push_back(tmp);
    }

    f_in >> amount >> dim;
    m_elems.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        FiniteElement tmp{};
        int nodeId;
        f_in >> tmp.m_id_var; //material
        tmp.m_nodes.reserve(dim);
        for (int j = 0; j < dim; ++j) {
            f_in >> nodeId;
            tmp.m_nodes.push_back(nodeId);
        }
        tmp.m_id = i;
        m_elems.push_back(std::move(tmp));
    }

    f_in >> amount >> dim;
    m_boundaries.reserve(amount);
    for (int i = 0; i < amount; ++i) {
        FiniteElement tmp{};
        int nodeId;
        f_in >> tmp.m_id_var; //surface
        for (int j = 0; j < dim; ++j) {
            f_in >> nodeId;
            tmp.m_nodes.push_back(nodeId);
        }
        tmp.m_id = i;
        m_boundaries.push_back(std::move(tmp));
    }
    std::cout << "Data was loaded successfully!" << std::endl;
}
