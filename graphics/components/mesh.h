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

    enum NormalType
    {
        CW,
        CCW
    };

    static Mesh ReadFromObjFile(const QString& filepath);

    void AddVertex(const Vertex& vertex);
    void AddEdge(const Edge& edge);
    void AddFace(const Face& face);

    void RemoveVertex(const int& index);
    void RemoveEdge(const int& index);
    void RemoveFace(const int& index);

    void Clear();

    QList<Vertex> GetVertices() const;
    QList<Edge> GetEdges() const;
    QList<Face> GetFaces() const;

    Vertex& GetVertex(const int& index);
    Edge& GetEdge(const int& index);
    Face& GetFace(const int& index);    

    int GetVerticesNum() const;
    int GetEdgesNum() const;
    int GetFacesNum() const;

    void SetNormalType(const NormalType& nt);
    NormalType GetNormalType() const;

private:
    QList<Vertex> m_vertices;
    QList<Edge> m_edges;
    QList<Face> m_faces;
    NormalType m_normalType;
};

#endif // MESH_H
