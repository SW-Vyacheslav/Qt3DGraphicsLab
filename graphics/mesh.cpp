#include "mesh.h"

Mesh::Mesh() {}

void Mesh::AddVertex(const Vertex& vertex)
{
    m_vertices.push_back(vertex);
}

void Mesh::RemoveVertex(const int& index)
{
    m_vertices.removeAt(index);
}

void Mesh::AddEdge(const Edge &edge)
{
    m_edges.push_back(edge);
}

void Mesh::RemoveEdge(const int &index)
{
    m_edges.removeAt(index);
}

void Mesh::AddFace(const Face& face)
{
    m_faces.push_back(face);
}

void Mesh::RemoveFace(const int& index)
{
    m_faces.removeAt(index);
}

void Mesh::Clear()
{
    m_vertices.clear();
    m_edges.clear();
    m_faces.clear();
}

QList<Vertex> Mesh::GetVertices()
{
    return m_vertices;
}

Vertex& Mesh::GetVertex(const int& index)
{
    return m_vertices[index];
}

int Mesh::GetVerticesNum() const
{
    return m_vertices.length();
}

Edge &Mesh::GetEdge(const int &index)
{
    return m_edges[index];
}

int Mesh::GetEdgesNum() const
{
    return m_edges.length();
}

Face& Mesh::GetFace(const int& index)
{
    return m_faces[index];
}

int Mesh::GetFacesNum() const
{
    return m_faces.length();
}

