#include "worldwidget.h"
#include <QPainter>
#include <thread>
#include <math.h>
#include "graphics/thorus.h"
#include "graphics/projections.h"
#include "graphics/components/transformmatrixcreator.h"
#include "math/Tools.h"

WorldWidget::WorldWidget(QWidget *parent) :
    QWidget(parent),
    m_worldObject(new Thorus()),
    m_projection(new FrontalProjection()),
    m_zBuffer(new ZBuffer(width(), height())),
    m_renderBuffer(new QImage(width(), height(), QImage::Format_RGB32)),
    m_drawBuffer(new QImage(width(), height(), QImage::Format_RGB32)),
    m_drawModel(WIREFRAME),
    m_shininess(1)
{
    connect(&m_worldObject->GetTransform(), SIGNAL(OnStateChanged()), this, SLOT(redraw()));
    m_zBuffer->Clear();
    m_renderBuffer->fill(Qt::black);
    m_drawBuffer->fill(Qt::black);
    m_projectionMatrix = Projection::CreateFrontalMatrix();
}

WorldWidget::~WorldWidget()
{
    std::lock_guard<std::mutex> ul(m_drawMutex);

    delete m_worldObject;
    delete m_projection;
    delete m_zBuffer;
    delete m_renderBuffer;
    delete m_drawBuffer;
}

void WorldWidget::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0, 0, *m_renderBuffer);
    painter.end();
}

void WorldWidget::resizeEvent(QResizeEvent *event)
{
    std::lock_guard<std::mutex> ul(m_drawMutex);
    m_coordSysCenter.SetX(event->size().width()/2);
    m_coordSysCenter.SetY(event->size().height()/2);
    delete m_zBuffer;
    m_zBuffer = new ZBuffer(event->size().width(), event->size().height());
    m_zBuffer->Clear();
    delete m_renderBuffer;
    m_renderBuffer = new QImage(event->size().width(), event->size().height(), QImage::Format_RGB32);
    delete m_drawBuffer;
    m_drawBuffer = new QImage(event->size().width(), event->size().height(), QImage::Format_RGB32);
    m_renderBuffer->fill(Qt::black);
}

void WorldWidget::drawObjectSurface()
{
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    if (objMesh.GetVerticesNum() == 0) return;
    QList<Vertex> posVerts = transformVertices(objMesh.GetVertices());
    recalculateNormals(posVerts);
    QList<Vertex> screenVerts = VerticesToCoordSystem(m_projection->Project(posVerts));
    m_zBuffer->Clear();
    m_drawBuffer->fill(Qt::black);
    for (int i = 0; i < objMesh.GetFacesNum(); ++i)
    {
        Face& face = objMesh.GetFace(i);
        Vector3D vertPos = (
                posVerts[face.vertexIndexes[0]].GetPosition() +
                posVerts[face.vertexIndexes[1]].GetPosition() +
                posVerts[face.vertexIndexes[2]].GetPosition()) *
                (1.0f/3.0f);
        Vector3D lightDir = m_light.getPosition() - vertPos;
        Vector3D reflDir = -lightDir - face.normal * Vector3D::DotProduct(-lightDir, face.normal) * 2;
        Vector3D viewDir = -vertPos;

        float dotProd = Vector3D::DotProduct(lightDir.GetNormalized(), face.normal.GetNormalized());
        dotProd = Tools::clamp(dotProd, 0.0f, 1.0f);

        float reflDotProd = Vector3D::DotProduct(reflDir.GetNormalized(), viewDir.GetNormalized());
        reflDotProd = Tools::clamp(reflDotProd, 0.0f, 1.0f);

        face.color = GetObjectLightningColor(dotProd, reflDotProd);
        fillTriangle(screenVerts[face.vertexIndexes[0]],
                screenVerts[face.vertexIndexes[1]],
                screenVerts[face.vertexIndexes[2]],
                face.color);
    }
}

void WorldWidget::drawObjectSurface2()
{
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    if (objMesh.GetVerticesNum() == 0) return;
    QList<Vertex> posVerts = transformVertices(objMesh.GetVertices());
    recalculateNormals(posVerts);
    QList<Vertex> projectedVerts;
    for (int i = 0; i < posVerts.length(); ++i)
    {
        Vertex projVert;
        Vector3D projVec;
        if (m_projectionMatrix.type == ProjectionMatrix::PERSPECTIVE)
        {
            float zBuf;
            projVec = posVerts[i].GetPosition() * m_projectionMatrix.viewTransformMatrix;
            zBuf = projVec.GetZ();
            projVec *= m_projectionMatrix.projectionMatrix;
            projVec.ToCartesian();
            projVec.SetZ(zBuf);
        }
        else
            projVec = posVerts[i].GetPosition() * m_projectionMatrix.projectionMatrix;
        projVert.SetPosition(projVec);
        projectedVerts.append(projVert);
    }
    projectedVerts = VerticesToCoordSystem(projectedVerts);
    m_zBuffer->Clear();
    m_drawBuffer->fill(Qt::black);
    for (int i = 0; i < objMesh.GetFacesNum(); ++i)
    {
        Face& face = objMesh.GetFace(i);
        Vector3D vertPos = (
                posVerts[face.vertexIndexes[0]].GetPosition() +
                posVerts[face.vertexIndexes[1]].GetPosition() +
                posVerts[face.vertexIndexes[2]].GetPosition()) *
                (1.0f/3.0f);
        Vector3D lightDir = m_light.getPosition() - vertPos;
        Vector3D reflDir = -lightDir - face.normal * Vector3D::DotProduct(-lightDir, face.normal) * 2;
        Vector3D viewDir = m_projectionMatrix.viewPosition - vertPos;

        float dotProd = Vector3D::DotProduct(lightDir.GetNormalized(), face.normal.GetNormalized());
        dotProd = Tools::clamp(dotProd, 0.0f, 1.0f);

        float reflDotProd = Vector3D::DotProduct(reflDir.GetNormalized(), viewDir.GetNormalized());
        reflDotProd = Tools::clamp(reflDotProd, 0.0f, 1.0f);

        face.color = GetObjectLightningColor(dotProd, reflDotProd);
        fillTriangle(projectedVerts[face.vertexIndexes[0]],
                projectedVerts[face.vertexIndexes[1]],
                projectedVerts[face.vertexIndexes[2]],
                face.color);
    }
}

void WorldWidget::drawObjectWireframe()
{
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    if (objMesh.GetVerticesNum() == 0) return;
    QList<Vertex> verts = VerticesToCoordSystem(m_projection->Project(transformVertices(objMesh.GetVertices())));
    m_drawBuffer->fill(Qt::black);
    for (int i = 0; i < objMesh.GetEdgesNum(); i++)
    {
        Edge& edge = objMesh.GetEdge(i);
        drawLine(static_cast<int>(verts[edge.vertexIndexes[0]].GetPosition().GetX()),
                static_cast<int>(verts[edge.vertexIndexes[0]].GetPosition().GetY()),
                static_cast<int>(verts[edge.vertexIndexes[1]].GetPosition().GetX()),
                static_cast<int>(verts[edge.vertexIndexes[1]].GetPosition().GetY()),
                Qt::white);
    }
    for (int i = 0; i < verts.length(); i++)
    {
        fillRect(static_cast<int>(verts[i].GetPosition().GetX()) - 1, static_cast<int>(verts[i].GetPosition().GetY()) - 1, 2, 2, Qt::red);
    }
}

void WorldWidget::drawMisc()
{
    Vertex lightPos;
    lightPos.SetPosition(m_light.getPosition());
    QList<Vertex> verts = VerticesToCoordSystem(m_projection->Project({lightPos}));
    fillRect(static_cast<int>(verts[0].GetPosition().GetX()) - 5, static_cast<int>(verts[0].GetPosition().GetY()) - 5, 10, 10, Qt::yellow);
}

QList<Vertex> WorldWidget::transformVertices(const QList<Vertex> &vertices)
{
    Transform& transform = m_worldObject->GetTransform();
    Matrix4x4 translateMat = TransformMatrixCreator::CreateTranslateMatrix(transform.GetPosition().GetX(),
                                                                           transform.GetPosition().GetY(),
                                                                           transform.GetPosition().GetZ());
    Matrix4x4 rotationMat = TransformMatrixCreator::CreateRotateMatrix(transform.GetRotation().GetX(),
                                                                       transform.GetRotation().GetY(),
                                                                       transform.GetRotation().GetZ());
    Matrix4x4 scaleMat = TransformMatrixCreator::CreateScaleMatrix(transform.GetScale().GetX(),
                                                                   transform.GetScale().GetY(),
                                                                   transform.GetScale().GetZ());

    QList<Vertex> verts;
    for (int i = 0; i < vertices.size(); ++i)
    {
        Vertex vert;
        vert.SetPosition(vertices[i].GetPosition() * scaleMat * rotationMat * translateMat);
        verts.append(vert);

    }
    return verts;
}

void WorldWidget::recalculateNormals(const QList<Vertex>& vertices)
{
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    for (int i = 0; i < objMesh.GetFacesNum(); ++i)
    {
        Face& face = objMesh.GetFace(i);
        Vector3D v1 = vertices[face.vertexIndexes[2]].GetPosition() -
                vertices[face.vertexIndexes[0]].GetPosition();
        Vector3D v2 = vertices[face.vertexIndexes[1]].GetPosition() -
                vertices[face.vertexIndexes[0]].GetPosition();
        face.normal = Vector3D::CrossProduct(v1, v2);
    }
}

QList<Vertex> WorldWidget::VerticesToCoordSystem(const QList<Vertex>& vertices)
{
    QList<Vertex> val;
    for(int i = 0; i < vertices.length(); i++)
    {
        Vertex vert;
        vert.SetPosition(m_coordSysCenter.GetX() + vertices[i].GetPosition().GetX(),
                         m_coordSysCenter.GetY() - vertices[i].GetPosition().GetY(),
                         vertices[i].GetPosition().GetZ());
        val.push_back(vert);
    }
    return val;
}

void WorldWidget::fillTriangle(const Vertex& vert1, const Vertex& vert2, const Vertex& vert3, const QColor &color)
{
    Vertex v1 = vert1;
    Vertex v2 = vert2;
    Vertex v3 = vert3;

    if (v2.GetPosition().GetY() < v1.GetPosition().GetY()) Tools::swap<Vertex>(v1, v2);
    if (v3.GetPosition().GetY() < v1.GetPosition().GetY()) Tools::swap<Vertex>(v1, v3);
    if (v3.GetPosition().GetY() < v2.GetPosition().GetY()) Tools::swap<Vertex>(v3, v2);

    int dy1 = static_cast<int>(v2.GetPosition().GetY() - v1.GetPosition().GetY());
    int dx1 = static_cast<int>(v2.GetPosition().GetX() - v1.GetPosition().GetX());
    int dy2 = static_cast<int>(v3.GetPosition().GetY() - v1.GetPosition().GetY());
    int dx2 = static_cast<int>(v3.GetPosition().GetX() - v1.GetPosition().GetX());
    float daxStep = 0;
    float dbxStep = 0;

    if (dy1 != 0) daxStep = dx1 / static_cast<float>(abs(dy1));
    if (dy2 != 0) dbxStep = dx2 / static_cast<float>(abs(dy2));

    if (dy1 != 0)
    {
        int y1 = static_cast<int>(v1.GetPosition().GetY());
        int y2 = static_cast<int>(v2.GetPosition().GetY());

        //optimization for out of bound drawing by y
        if (y1 < 0) y1 = 0;
        if (y2 < 0) y2 = 0;
        if (y2 >= height()) y2 = height() - 1;
        if (y1 >= height())
        {
            y1 = 0;
            y2 = 0;
        }

        for (int i = y1; i <= y2; i++)
        {
            int ax = static_cast<int>(v1.GetPosition().GetX() + (i - v1.GetPosition().GetY()) * daxStep);
            int bx = static_cast<int>(v1.GetPosition().GetX() + (i - v1.GetPosition().GetY()) * dbxStep);

            if (ax > bx) Tools::swap<int>(ax, bx);

            //optimization for out of bound drawing by x
            if (ax < 0) ax = 0;
            if (bx >= width()) bx = width() - 1;
            if (bx < 0) break;
            if (ax >= width()) break;

            for (int j = ax; j < bx; j++)
            {
                if (m_zBuffer->CheckAndSet(j, i, v1.GetPosition().GetZ()))
                {
                    drawPixel(j, i, color);
                }
            }

        }
    }

    dy1 = static_cast<int>(v3.GetPosition().GetY() - v2.GetPosition().GetY());
    dx1 = static_cast<int>(v3.GetPosition().GetX() - v2.GetPosition().GetX());

    if (dy1 != 0) daxStep = dx1 / static_cast<float>(abs(dy1));

    if (dy1 != 0)
    {
        int y1 = static_cast<int>(v2.GetPosition().GetY());
        int y2 = static_cast<int>(v3.GetPosition().GetY());

        //optimization for out of bound drawing by y
        if (y1 < 0) y1 = 0;
        if (y2 < 0) y2 = 0;
        if (y2 >= height()) y2 = height() - 1;
        if (y1 >= height())
        {
            y1 = 0;
            y2 = 0;
        }

        for (int i = y1; i <= y2; i++)
        {
            int ax = static_cast<int>(v2.GetPosition().GetX() + (i - v2.GetPosition().GetY()) * daxStep);
            int bx = static_cast<int>(v1.GetPosition().GetX() + (i - v1.GetPosition().GetY()) * dbxStep);

            if (ax > bx) Tools::swap<int>(ax, bx);

            //optimization for out of bound drawing by x
            if (ax < 0) ax = 0;
            if (bx >= width()) bx = width() - 1;
            if (bx < 0) break;
            if (ax >= width()) break;

            for (int j = ax; j < bx; j++)
            {
                if (m_zBuffer->CheckAndSet(j, i, v1.GetPosition().GetZ()))
                {
                    drawPixel(j, i, color);
                }
            }

        }
    }
}

void WorldWidget::fillRect(const int &x, const int &y, const int &width, const int &height, const QColor &color)
{
    int y1 = y;
    int x2 = x + width;
    int y2 = y + height;

    while (y1 != y2)
    {
        drawLine(x, y1, x2, y1, color);
        ++y1;
    }
}

void WorldWidget::drawLine(const int &x1, const int &y1, const int &x2, const int &y2, const QColor &color)
{
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    int x = x1;
    int y = y1;
    int xend = x2;
    int yend = y2;

    if (dx == dy)
    {
        int incy = y < yend ? 1 : -1;
        int incx = x < xend ? 1 : -1;

        drawPixel(x, y, color);
        while (x != xend || y != yend)
        {
            x += incx;
            y += incy;
            drawPixel(x, y, color);
        }
        return;
    }
    else if (dx == 0)
    {
        int incy = y < yend ? 1 : -1;

        drawPixel(x, y, color);
        while (y != yend)
        {
            y += incy;
            drawPixel(x, y, color);
        }
        return;
    }
    else if (dy == 0)
    {
        int incx = x < xend ? 1 : -1;

        drawPixel(x, y, color);
        while (x != xend)
        {
            x += incx;
            drawPixel(x, y, color);
        }
        return;
    }

    bool inv = false;

    if (dx < dy)
    {
        inv = true;
        Tools::swap(dx, dy);
        Tools::swap(x, y);
        Tools::swap(xend, yend);
    }

    if (x > xend)
    {
        Tools::swap(x, xend);
        Tools::swap(y, yend);
    }

    int incy = y < yend ? 1 : -1;

    int d = (dy << 1) - dx;

    drawPixel(inv ? yend : xend, inv ? xend : yend, color);
    while (x != xend || y != yend)
    {
        drawPixel(inv ? y : x, inv ? x : y, color);

        if (d >= 0)
        {
            y += incy;
            d -= (dx << 1);
        }

        d += (dy << 1);
        x++;
    }
}

void WorldWidget::drawPixel(const int &x, const int &y, const QColor &color)
{
    if ((x < 0) || (x >= width())) return;
    if ((y < 0) || (y >= height())) return;
    m_drawBuffer->setPixelColor(x, y, color);
}

QRgb WorldWidget::GetObjectLightningColor(const float &dotProd, const float &reflectDotProd)
{
    float red = m_ambientColor.getRed() * m_ambientMaterialReflection.getRed() +
            m_diffuseColor.getRed() * m_diffuseMaterialReflection.getRed() * dotProd +
            m_specularColor.getRed() * m_specularMaterialReflection.getRed() * powf(reflectDotProd, m_shininess);

    float green = m_ambientColor.getGreen() * m_ambientMaterialReflection.getGreen() +
            m_diffuseColor.getGreen() * m_diffuseMaterialReflection.getGreen() * dotProd +
            m_specularColor.getGreen() * m_specularMaterialReflection.getGreen() * powf(reflectDotProd, m_shininess);

    float blue = m_ambientColor.getBlue() * m_ambientMaterialReflection.getBlue() +
            m_diffuseColor.getBlue() * m_diffuseMaterialReflection.getBlue() * dotProd +
            m_specularColor.getBlue() * m_specularMaterialReflection.getBlue() * powf(reflectDotProd, static_cast<float>(m_shininess));

    return qRgb(static_cast<int>(Tools::scaleInRange(red, 0, 3, 0, 255)),
                              static_cast<int>(Tools::scaleInRange(green, 0, 3, 0, 255)),
                              static_cast<int>(Tools::scaleInRange(blue, 0, 3, 0, 255)));
}

WorldObject& WorldWidget::GetWorldObject()
{
    return *m_worldObject;
}

void WorldWidget::SetProjection(Projection *projection)
{
    delete m_projection;
    m_projection = projection;
    redraw();
}

void WorldWidget::SetProjectionMatrix(const ProjectionMatrix &projMat)
{
    m_projectionMatrix = projMat;
}

void WorldWidget::SetAmbientColor(const ColorN &color)
{
    m_ambientColor = color;
}

void WorldWidget::SetAmbientMaterialReflection(const ColorN &matRefl)
{
    m_ambientMaterialReflection = matRefl;
}

void WorldWidget::SetDiffuseColor(const ColorN &color)
{
    m_diffuseColor = color;
}

void WorldWidget::SetDiffuseMaterialReflection(const ColorN &matRefl)
{
    m_diffuseMaterialReflection = matRefl;
}

void WorldWidget::SetSpecularColor(const ColorN &color)
{
    m_specularColor = color;
}

void WorldWidget::SetSpecularMaterialReflection(const ColorN &matRefl)
{
    m_specularMaterialReflection = matRefl;
}

void WorldWidget::SetShininess(const int &shininess)
{
    m_shininess = shininess;
}

void WorldWidget::SetDrawModel(const WorldWidget::DrawModel &drawModel)
{
    m_drawModel = drawModel;
    redraw();
}

void WorldWidget::SetLight(const Vector3D &light)
{
    m_light.setPosition(light);
    redraw();
}

void WorldWidget::redraw()
{
    std::thread rt(&WorldWidget::redrawThread, this);
    rt.detach();
}

void WorldWidget::redrawThread()
{
    std::lock_guard<std::mutex> lock(m_drawMutex);
    switch (m_drawModel)
    {
    case WIREFRAME:
        drawObjectWireframe();
        break;
    case SURFACE:
        drawObjectSurface2();
        break;
    }
    drawMisc();
    *m_renderBuffer = m_drawBuffer->copy();
    update();
}
