#include "DataStructures.h"

/// constructors

Node::Node(int p_id, const std::vector<double> &p_coordinates, bool p_vertex) :
                            m_id(p_id),
                            m_coordinates(p_coordinates),
                            m_vertex(p_vertex) {}

Edge::Edge(int first_id, int second_id, int mid_id) : m_nodes({first_id, second_id}), m_mid(mid_id) {}

FiniteElement::FiniteElement(int p_id, std::vector<int>& p_nodes) :
        m_id(p_id),
        m_nodes(p_nodes) {}

/// methods
bool Edge::operator==(const Edge &edge) const {
    return (m_nodes.first == edge.m_nodes.first) && (m_nodes.second == edge.m_nodes.second);
}

/// input/output operators

std::istream& operator>>(std::istream &p_in, Node &p_node){
    p_in >> p_node.m_id;
    p_in >> p_node.m_coordinates[0] >> p_node.m_coordinates[1] >> p_node.m_coordinates[2];
    p_in >> p_node.m_vertex;
    return p_in;
}

std::ostream &operator<<(std::ostream &p_out, const Node &p_node){
    p_out << "node №" << p_node.m_id << "\n";
    p_out << p_node.m_coordinates[0] << " " << p_node.m_coordinates[1] << " " << p_node.m_coordinates[2] << "\n";
    p_out << "is vertex: " << std::boolalpha << p_node.m_vertex << "\n";
    return p_out;
}

std::istream& operator>>(std::istream &p_in, Edge &edge){
    p_in >> edge.m_nodes.first >> edge.m_nodes.second;
    return p_in;
}


std::ostream& operator<<(std::ostream &p_out, const Edge &edge){
    p_out <<'(' << edge.m_nodes.first << ", " << edge.m_nodes.second << ')';
    return p_out;
}

std::istream& operator>>(std::istream &p_in, FiniteElement &elem){
    p_in >> elem.m_id;

    for(auto node :elem.m_nodes)
        p_in >> node;

    return p_in;
}

std::ostream& operator<<(std::ostream &p_out, const FiniteElement &elem){
    p_out << "finite element №" << elem.m_id<< "\n";
    p_out << "surface/material №" << elem.m_id_var << "\n";

    p_out << "( ";
    for(auto node :elem.m_nodes )
        p_out << node << ' ';
    p_out << ")";

    return p_out;
}

