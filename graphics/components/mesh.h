#ifndef MESH_H
#define MESH_H

#include <QList>
#include "graphics/components/vertex.h"
#include "graphics/components/edge.h"
#include "graphics/components/face.h"

class Mesh
{
public:
    Mesh();

    void AddVertex(const Vertex& vertex);
    void RemoveVertex(const int& index);

    void AddEdge(const Edge& edge);
    void RemoveEdge(const int& index);

    void AddFace(const Face& face);
    void RemoveFace(const int& index);

    void Clear();

    QList<Vertex> GetVertices() const;

    Vertex& GetVertex(const int& index);
    int GetVerticesNum() const;

    Edge& GetEdge(const int& index);
    int GetEdgesNum() const;

    Face& GetFace(const int& index);
    int GetFacesNum() const;

private:
    QList<Vertex> m_vertices;
    QList<Face> m_faces;
    QList<Edge> m_edges;
};

#endif // MESH_H
