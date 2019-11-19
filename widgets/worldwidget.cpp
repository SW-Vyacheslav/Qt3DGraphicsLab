#include "worldwidget.h"
#include <QPainter>
#include "graphics/thorus.h"
#include "graphics/projections.h"

WorldWidget::WorldWidget(QWidget *parent) : QWidget(parent)
{
    m_projection = new FrontalProjection();
    m_worldObject = new Thorus();
}

void WorldWidget::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    drawObject(painter);
    painter.end();
}

void WorldWidget::resizeEvent(QResizeEvent *event)
{
    m_coordSysCenter.SetX(event->size().width()/2);
    m_coordSysCenter.SetY(event->size().height()/2);
}

void WorldWidget::drawObject(QPainter& painter)
{
    Thorus* thorus = static_cast<Thorus*>(m_worldObject);
    Mesh& objMesh = thorus->GetMesh();
    QList<Vertex> verts = VerticesToCoordSystem(m_projection->Project(objMesh.GetVertices()));
    painter.fillRect(0, 0, width(), height(), Qt::black);
    if (true)
    {
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
    }
    if (true)
    {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        for (int i = 0; i < verts.length(); i++)
        {
            painter.drawRect(static_cast<int>(verts[i].GetPosition().GetX()) - 1, static_cast<int>(verts[i].GetPosition().GetY()) - 1, 2, 2);
        }
    }

    Vertex opCenter;
    opCenter.SetPosition(thorus->GetTransform().GetOpPosition());
    verts = VerticesToCoordSystem(m_projection->Project({opCenter}));
    painter.setPen(Qt::yellow);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(static_cast<int>(verts[0].GetPosition().GetX())-5, static_cast<int>(verts[0].GetPosition().GetY())-5, 10, 10);
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

WorldObject& WorldWidget::GetWorldObject()
{
    return *m_worldObject;
}
