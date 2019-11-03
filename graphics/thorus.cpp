#include "graphics/thorus.h"
#include "graphics/components/mesh.h"
#include "graphics/components/vertex.h"
#include "math/Converter.h"

Thorus::Thorus() {}

void Thorus::Construct(const int &n, const int &m, const int &R, const int &r)
{
    GetMesh().Clear();

    float RStep = 360.0f / m;
    float rStep = 360.0f / n;

    float rAngle = -180;
    float RAngle = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Vertex vert;
            vert.SetPosition(
                        (R + r * cosf(Converter::DegreesToRadians(rAngle))) * cosf(Converter::DegreesToRadians(RAngle)),
                        (R + r * cosf(Converter::DegreesToRadians(rAngle))) * sinf(Converter::DegreesToRadians(RAngle)),
                        r * sinf(Converter::DegreesToRadians(rAngle)));
            GetMesh().AddVertex(vert);
            rAngle += rStep;
        }
        rAngle = -180;
        RAngle += RStep;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Edge edge;
            if(j + 1 == n)
            {
                edge.vertexIndexes[0] = j + (i * n);
                edge.vertexIndexes[1] = j + (i * n) - n + 1;
            }
            else
            {
                edge.vertexIndexes[0] = j + (i * n);
                edge.vertexIndexes[1] = j + (i * n) + 1;
            }
            GetMesh().AddEdge(edge);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Edge edge;
            if((i + 1) != m)
            {
                edge.vertexIndexes[0] = j + (i * n);
                edge.vertexIndexes[1] = j + ((i + 1) * n);
            }
            else
            {
                edge.vertexIndexes[0] = j + (i * n);
                edge.vertexIndexes[1] = j;
            }
            GetMesh().AddEdge(edge);
        }
    }
}
