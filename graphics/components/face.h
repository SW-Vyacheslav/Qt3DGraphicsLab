#ifndef FACE_H
#define FACE_H

#include <QRgb>
#include "math/Vector3D.h"

struct Face
{
    int vertexIndexes[3] = {};
    Vector3D normal;
    QRgb color;
};

#endif // FACE_H
