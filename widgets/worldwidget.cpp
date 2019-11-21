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
    drawMisc();
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
    painter.end();
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    QList<Vertex> verts = VerticesToCoordSystem(m_projection->Project(transformVertices(objMesh.GetVertices())));
    m_zBuffer->Clear();
    for (int i = 0; i < objMesh.GetFacesNum(); ++i)
    {
        Face& face = objMesh.GetFace(i);
        fillTriangle(verts[face.vertexIndexes[0]],
                verts[face.vertexIndexes[1]],
                verts[face.vertexIndexes[2]],
                face.color);
    }
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

void WorldWidget::fillTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const QRgb &color)
{


    QPainter painter;
    painter.begin(this);

    painter.end();
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
