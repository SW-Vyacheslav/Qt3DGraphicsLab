#include "worldwidget.h"
#include <QPainter>
#include "graphics/thorus.h"
#include "graphics/projections.h"
#include "graphics/components/transformmatrixcreator.h"

WorldWidget::WorldWidget(QWidget *parent) :
    QWidget(parent),
    m_worldObject(new Thorus()),
    m_projection(new FrontalProjection()),
    m_zBuffer(new ZBuffer(width(), height())),
    m_drawModel(WIREFRAME)
{
    connect(&m_worldObject->GetTransform(), SIGNAL(OnStateChanged()), this, SLOT(update()));
    m_zBuffer->Clear();
}

void WorldWidget::paintEvent(QPaintEvent*)
{
    switch (m_drawModel)
    {
    case WIREFRAME:
        drawObjectWireframe();
        break;
    case SURFACE:
        drawObjectSurface();
        break;
    }
    //drawMisc();
}

void WorldWidget::resizeEvent(QResizeEvent *event)
{
    m_coordSysCenter.SetX(event->size().width()/2);
    m_coordSysCenter.SetY(event->size().height()/2);
    delete m_zBuffer;
    m_zBuffer = new ZBuffer(event->size().width(), event->size().height());
    m_zBuffer->Clear();
}

void WorldWidget::drawObjectSurface()
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(0, 0, width(), height(), Qt::black);
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    QList<Vertex> verts = transformVertices(objMesh.GetVertices());
    recalculateNormals(verts);
    verts = VerticesToCoordSystem(m_projection->Project(verts));
    m_zBuffer->Clear();
    Vector3D light(0.0f, 0.0f, -100.0f);
    for (int i = 0; i < objMesh.GetFacesNum(); ++i)
    {
        Face& face = objMesh.GetFace(i);
        float dotProd = Vector3D::DotProduct(light.GetNormalized(), face.normal);
        QColor col;
        col.setHsl(0, 0, static_cast<int>(dotProd * 100));
        col.toRgb();
        face.color = qRgb(col.red(), col.green(), col.blue());
        fillTriangle(verts[face.vertexIndexes[0]],
                verts[face.vertexIndexes[1]],
                verts[face.vertexIndexes[2]],
                face.color);
    }
    painter.end();
}

void WorldWidget::drawObjectWireframe()
{
    QPainter painter;
    painter.begin(this);
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    QList<Vertex> verts = VerticesToCoordSystem(m_projection->Project(transformVertices(objMesh.GetVertices())));
    painter.fillRect(0, 0, width(), height(), Qt::black);
    painter.setPen(Qt::white);
    for (int i = 0; i < objMesh.GetEdgesNum(); i++)
    {
        Edge& edge = objMesh.GetEdge(i);
        painter.drawLine(
                    static_cast<int>(verts[edge.vertexIndexes[0]].GetPosition().GetX()),
                    static_cast<int>(verts[edge.vertexIndexes[0]].GetPosition().GetY()),
                    static_cast<int>(verts[edge.vertexIndexes[1]].GetPosition().GetX()),
                    static_cast<int>(verts[edge.vertexIndexes[1]].GetPosition().GetY()));
    }

    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    for (int i = 0; i < verts.length(); i++)
    {
        painter.drawRect(static_cast<int>(verts[i].GetPosition().GetX()) - 1, static_cast<int>(verts[i].GetPosition().GetY()) - 1, 2, 2);
    }
    painter.end();
}

void WorldWidget::drawMisc()
{
    QPainter painter;
    painter.begin(this);
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Vertex opCenter;
    opCenter.SetPosition(thorus->GetTransform().GetOpPosition());
    QList<Vertex> verts = VerticesToCoordSystem(m_projection->Project({opCenter}));
    painter.setPen(Qt::yellow);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(static_cast<int>(verts[0].GetPosition().GetX())-5, static_cast<int>(verts[0].GetPosition().GetY())-5, 10, 10);
    painter.end();
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
        Vector3D v1 = vertices[face.vertexIndexes[1]].GetPosition() -
                vertices[face.vertexIndexes[0]].GetPosition();
        Vector3D v2 = vertices[face.vertexIndexes[2]].GetPosition() -
                vertices[face.vertexIndexes[0]].GetPosition();
        face.normal = Vector3D::CrossProduct(v2, v1).GetNormalized();
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

void WorldWidget::fillTriangle(Vertex v1, Vertex v2, Vertex v3, const QRgb &color)
{
    QPainter painter;
    painter.begin(this);
    painter.setPen(color);
    painter.setBrush(QBrush(color));

    if (v2.GetPosition().GetY() < v1.GetPosition().GetY()) swapVerts(v1, v2);
    if (v3.GetPosition().GetY() < v1.GetPosition().GetY()) swapVerts(v1, v3);
    if (v3.GetPosition().GetY() < v2.GetPosition().GetY()) swapVerts(v3, v2);

    int dy1 = static_cast<int>(v2.GetPosition().GetY() - v1.GetPosition().GetY());
    int dx1 = static_cast<int>(v2.GetPosition().GetX() - v1.GetPosition().GetX());
    int dy2 = static_cast<int>(v3.GetPosition().GetY() - v1.GetPosition().GetY());
    int dx2 = static_cast<int>(v3.GetPosition().GetX() - v1.GetPosition().GetX());
    float daxStep = 0;
    float dbxStep = 0;

    if (dy1) daxStep = dx1 / static_cast<float>(abs(dy1));
    if (dy2) dbxStep = dx2 / static_cast<float>(abs(dy2));

    if (dy1)
    {
        for (int i = static_cast<int>(v1.GetPosition().GetY()); i <= static_cast<int>(v2.GetPosition().GetY()); i++)
        {
            int ax = static_cast<int>(v1.GetPosition().GetX() + (i - v1.GetPosition().GetY()) * daxStep);
            int bx = static_cast<int>(v1.GetPosition().GetX() + (i - v1.GetPosition().GetY()) * dbxStep);

            if (ax > bx)
            {
                int temp = ax;
                ax = bx;
                bx = temp;
            }

            for (int j = ax; j < bx; j++)
            {
                if (m_zBuffer->CheckAndSet(j, i, v1.GetPosition().GetZ()))
                {
                    painter.drawPoint(j, i);
                }
            }

        }
    }

    dy1 = static_cast<int>(v3.GetPosition().GetY() - v2.GetPosition().GetY());
    dx1 = static_cast<int>(v3.GetPosition().GetX() - v2.GetPosition().GetX());

    if (dy1) daxStep = dx1 / static_cast<float>(abs(dy1));

    if (dy1)
    {
        for (int i = static_cast<int>(v2.GetPosition().GetY()); i <= static_cast<int>(v3.GetPosition().GetY()); i++)
        {
            int ax = static_cast<int>(v2.GetPosition().GetX() + (i - v2.GetPosition().GetY()) * daxStep);
            int bx = static_cast<int>(v1.GetPosition().GetX() + (i - v1.GetPosition().GetY()) * dbxStep);

            if (ax > bx)
            {
                int temp = ax;
                ax = bx;
                bx = temp;
            }

            for (int j = ax; j < bx; j++)
            {
                if (m_zBuffer->CheckAndSet(j, i, v1.GetPosition().GetZ()))
                {
                    painter.drawPoint(j, i);
                }
            }

        }
    }

    painter.end();
}

void WorldWidget::swapVerts(Vertex &v1, Vertex &v2)
{
    Vertex temp = v1;
    v1 = v2;
    v2 = temp;
}

WorldObject& WorldWidget::GetWorldObject()
{
    return *m_worldObject;
}

void WorldWidget::SetProjection(Projection *projection)
{
    delete m_projection;
    m_projection = projection;
    update();
}

void WorldWidget::SetDrawModel(const WorldWidget::DrawModel &drawModel)
{
    m_drawModel = drawModel;
    update();
}
