#include "graphics/components/mesh.h"
#include <QFile>
#include <QTextStream>

Mesh::Mesh() : m_normalType(CCW) {}

Mesh Mesh::ReadFromObjFile(const QString &filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return Mesh();

    Mesh ret_val;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QStringList strlist = in.readLine().split(' ');
        if (strlist[0] == "v")
        {
            Vertex vert;
            vert.SetPosition(strlist[1].toFloat(), strlist[2].toFloat(), strlist[3].toFloat());
            ret_val.AddVertex(vert);
        }
        if (strlist[0] == "f")
        {
            strlist[1] = strlist[1].split('/')[0];
            strlist[2] = strlist[2].split('/')[0];
            strlist[3] = strlist[3].split('/')[0];

            Face face;
            face.vertexIndexes[0] = (strlist[1].toInt() >= 0) ? strlist[1].toInt() : -strlist[1].toInt();
            face.vertexIndexes[1] = (strlist[2].toInt() >= 0) ? strlist[2].toInt() : -strlist[2].toInt();
            face.vertexIndexes[2] = (strlist[3].toInt() >= 0) ? strlist[3].toInt() : -strlist[3].toInt();
            face.vertexIndexes[0] -= 1;
            face.vertexIndexes[1] -= 1;
            face.vertexIndexes[2] -= 1;

            ret_val.AddFace(face);
        }
    }
    return ret_val;
}

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

void Mesh::SetNormalType(const Mesh::NormalType &nt)
{
    m_normalType = nt;
}

Mesh::NormalType Mesh::GetNormalType() const
{
    return m_normalType;
}

