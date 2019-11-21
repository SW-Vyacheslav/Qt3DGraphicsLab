#ifndef THORUS_H
#define THORUS_H

#include <QObject>
#include "graphics/components/mesh.h"
#include "graphics/components/worldobject.h"

class Thorus : public QObject, public WorldObject
{
    Q_OBJECT

public:
    Thorus();
    Thorus(const int& baseApprox, const int& generatrixApprox, const int& baseRadius, const int& generatrixRadius);

    void Construct();
    void RecalculateNormals();

    int GetBaseApprox() const;
    int GetGeneratrixApprox() const;
    int GetBaseRadius() const;
    int GetGeneratrixRadius() const;
    Mesh& GetMesh();

public slots:
    void SetBaseApprox(const int& baseApprox);
    void SetGeneratrixApprox(const int& generatrixApprox);
    void SetBaseRadius(const int& baseRadius);
    void SetGeneratrixRadius(const int& generatrixRadius);

signals:
    void OnBaseApproxChanged(const int& newValue);
    void OnGeneratixApproxChanged(const int& newValue);
    void OnBaseRadiusChanged(const int& newValue);
    void OnGeneratixRadiusChanged(const int& newValue);

private:
    int m_baseApprox;
    int m_generatrixApprox;
    int m_baseRadius;
    int m_generatrixRadius;
    Mesh m_mesh;
};

#endif // THORUS_H
