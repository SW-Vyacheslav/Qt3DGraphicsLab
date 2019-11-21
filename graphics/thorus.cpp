#include "graphics/thorus.h"
#include "graphics/components/mesh.h"
#include "graphics/components/vertex.h"
#include "math/Converter.h"

Thorus::Thorus():
    QObject(nullptr),
    m_baseApprox(1),
    m_generatrixApprox(1),
    m_baseRadius(1),
    m_generatrixRadius(1)
{}

Thorus::Thorus(const int& baseApprox,
               const int& generatrixApprox,
               const int& baseRadius,
               const int& generatrixRadius) :
    QObject(nullptr),
    m_baseApprox(baseApprox),
    m_generatrixApprox(generatrixApprox),
    m_baseRadius(baseRadius),
    m_generatrixRadius(generatrixRadius)
{}

void Thorus::Construct()
{
    GetMesh().Clear();

    float RStep = 360.0f / m_baseApprox;
    float rStep = 360.0f / m_generatrixApprox;
    float RAngle = 0;
    float rAngle = -180;

    for (int i = 0; i < m_baseApprox; ++i)
    {
        for (int j = 0; j < m_generatrixApprox; ++j)
        {
            Vertex vert;
            vert.SetPosition(
                        (m_baseRadius + m_generatrixRadius * cosf(Converter::DegreesToRadians(rAngle))) * cosf(Converter::DegreesToRadians(RAngle)),
                        (m_baseRadius + m_generatrixRadius * cosf(Converter::DegreesToRadians(rAngle))) * sinf(Converter::DegreesToRadians(RAngle)),
                        m_generatrixRadius * sinf(Converter::DegreesToRadians(rAngle)));
            GetMesh().AddVertex(vert);
            rAngle += rStep;
        }
        rAngle = -180;
        RAngle += RStep;
    }

    for (int i = 0; i < m_baseApprox; ++i)
    {
        for (int j = 0; j < m_generatrixApprox; ++j)
        {
            Edge edge;
            if(j + 1 == m_generatrixApprox)
            {
                edge.vertexIndexes[0] = j + (i * m_generatrixApprox);
                edge.vertexIndexes[1] = j + (i * m_generatrixApprox) - m_generatrixApprox + 1;
            }
            else
            {
                edge.vertexIndexes[0] = j + (i * m_generatrixApprox);
                edge.vertexIndexes[1] = j + (i * m_generatrixApprox) + 1;
            }
            GetMesh().AddEdge(edge);
        }
    }

    for (int i = 0; i < m_baseApprox; ++i)
    {
        for (int j = 0; j < m_generatrixApprox; ++j)
        {
            Edge edge;
            if((i + 1) != m_baseApprox)
            {
                edge.vertexIndexes[0] = j + (i * m_generatrixApprox);
                edge.vertexIndexes[1] = j + ((i + 1) * m_generatrixApprox);
            }
            else
            {
                edge.vertexIndexes[0] = j + (i * m_generatrixApprox);
                edge.vertexIndexes[1] = j;
            }
            GetMesh().AddEdge(edge);
        }
    }

    for (int i = 0; i < m_baseApprox; ++i)
    {
        for (int j = 0; j < m_generatrixApprox; ++j)
        {
            Face face;
            if ((j + 1 != m_generatrixApprox) && (i + 1 != m_baseApprox))
            {
                face.vertexIndexes[0] = j + (i * m_generatrixApprox);
                face.vertexIndexes[1] = j + (i * m_generatrixApprox) + 1;
                face.vertexIndexes[2] = j + ((i + 1) * m_generatrixApprox);
                GetMesh().AddFace(face);
                face.vertexIndexes[0] = j + ((i + 1) * m_generatrixApprox) + 1;
                face.vertexIndexes[1] = j + ((i + 1) * m_generatrixApprox);
                face.vertexIndexes[2] = j + (i * m_generatrixApprox) + 1;
                GetMesh().AddFace(face);
            }
            else if ((j + 1 == m_generatrixApprox) && (i + 1 != m_baseApprox))
            {
                face.vertexIndexes[0] = j + (i * m_generatrixApprox);
                face.vertexIndexes[1] = j + (i * m_generatrixApprox) - m_generatrixApprox + 1;
                face.vertexIndexes[2] = j + ((i + 1) * m_generatrixApprox);
                GetMesh().AddFace(face);
                face.vertexIndexes[0] = j + ((i + 1) * m_generatrixApprox) - m_generatrixApprox + 1;
                face.vertexIndexes[1] = j + ((i + 1) * m_generatrixApprox);
                face.vertexIndexes[2] = j + (i * m_generatrixApprox) - m_generatrixApprox + 1;
                GetMesh().AddFace(face);
            }
            else if ((j + 1 != m_generatrixApprox) && (i + 1 == m_baseApprox))
            {
                face.vertexIndexes[0] = j + (i * m_generatrixApprox);
                face.vertexIndexes[1] = j + (i * m_generatrixApprox) + 1;
                face.vertexIndexes[2] = j;
                GetMesh().AddFace(face);
                face.vertexIndexes[0] = j + 1;
                face.vertexIndexes[1] = j;
                face.vertexIndexes[2] = j + (i * m_generatrixApprox) + 1;
                GetMesh().AddFace(face);
            }
            else
            {
                face.vertexIndexes[0] = j + (i * m_generatrixApprox);
                face.vertexIndexes[1] = j + (i * m_generatrixApprox) - m_generatrixApprox + 1;
                face.vertexIndexes[2] = j;
                GetMesh().AddFace(face);
                face.vertexIndexes[0] = j - m_generatrixApprox + 1;
                face.vertexIndexes[1] = j;
                face.vertexIndexes[2] = j + (i * m_generatrixApprox) - m_generatrixApprox + 1;
                GetMesh().AddFace(face);
            }
        }
    }
}

int Thorus::GetBaseApprox() const
{
    return m_baseApprox;
}

int Thorus::GetGeneratrixApprox() const
{
    return m_generatrixApprox;
}

int Thorus::GetBaseRadius() const
{
    return m_baseRadius;
}

int Thorus::GetGeneratrixRadius() const
{
    return m_generatrixRadius;
}

Mesh &Thorus::GetMesh()
{
    return m_mesh;
}

void Thorus::SetBaseApprox(const int& baseApprox)
{
    m_baseApprox = baseApprox;
    emit OnBaseApproxChanged(m_baseApprox);
}

void Thorus::SetGeneratrixApprox(const int& generatrixApprox)
{
    m_generatrixApprox = generatrixApprox;
    emit OnGeneratixApproxChanged(m_generatrixApprox);
}

void Thorus::SetBaseRadius(const int& baseRadius)
{
    m_baseRadius = baseRadius;
    emit OnBaseRadiusChanged(m_baseRadius);
}

void Thorus::SetGeneratrixRadius(const int& generatrixRadius)
{
    m_generatrixRadius = generatrixRadius;
    emit OnGeneratixRadiusChanged(m_generatrixRadius);
}


