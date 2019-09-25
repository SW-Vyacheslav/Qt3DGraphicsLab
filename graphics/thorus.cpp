#include "thorus.h"
#include "mesh.h"
#include "vertex.h"
#include "math/Converter.h"

Thorus::Thorus() {}

void Thorus::Construct(const int &n, const int &m, const int &R, const int &r)
{
    GetMesh().Clear();

    int rStep = 360 / n;
    int RStep = 360 / m;

    int maxRAngle = (RStep % m == 0) ? 360 : RStep * m;
    int maxrAngle = (rStep % n == 0) ? 180 : RStep * m - 180;

    for (int RAngle = 0; RAngle < maxRAngle; RAngle += RStep)
    {
        for (int rAngle = -180; rAngle < maxrAngle; rAngle += rStep)
        {
            Vertex vert;
            vert.GetPosition().SetX((R + r * cosf(Converter::DegreesToRadians(rAngle))) * cosf(Converter::DegreesToRadians(RAngle)));
            vert.GetPosition().SetY((R + r * cosf(Converter::DegreesToRadians(rAngle))) * sinf(Converter::DegreesToRadians(RAngle)));
            vert.GetPosition().SetZ(r * sinf(Converter::DegreesToRadians(rAngle)));
            GetMesh().AddVertex(vert);
        }
    }
}
