#include "graphics/components/mesh.h"

Mesh::Mesh() {}

void Mesh::AddVertex(const Vertex& vertex)
{
    m_vertices.push_back(vertex);
}

void Mesh::AddEdge(const Edge &edge)
{
    m_edges.push_back(edge);
}

void Mesh::AddFace(const Face& face)
{
    m_faces.push_back(face);
}

void Mesh::RemoveVertex(const int& index)
{
    m_vertices.removeAt(index);
}

void Mesh::RemoveEdge(const int &index)
{
    m_edges.removeAt(index);
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

QList<Vertex> Mesh::GetVertices() const
{
    return m_vertices;
}

QList<Edge> Mesh::GetEdges() const
{
    return m_edges;
}

QList<Face> Mesh::GetFaces() const
{
    return m_faces;
}

Vertex& Mesh::GetVertex(const int& index)
{
    return m_vertices[index];
}

Edge &Mesh::GetEdge(const int &index)
{
    return m_edges[index];
}

Face& Mesh::GetFace(const int& index)
{
    return m_faces[index];
}

int Mesh::GetVerticesNum() const
{
    return m_vertices.length();
}

int Mesh::GetEdgesNum() const
{
    return m_edges.length();
}

int Mesh::GetFacesNum() const
{
    return m_faces.length();
}

