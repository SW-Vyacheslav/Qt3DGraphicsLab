#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/vertex.h"
#include "graphics/mesh.h"
#include "graphics/thorus.h"
#include "graphics/frontalprojection.h"
#include "graphics/horizontalprojection.h"
#include "graphics/profileprojection.h"
#include "graphics/axonometricprojection.h"
#include "graphics/obliqueprojection.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->outputWidget->installEventFilter(this);
    ui->mVal->setRange(3, 50);
    ui->nVal->setRange(3, 50);
    ui->RVal->setRange(1, 1000);
    ui->rVal->setRange(1, 1000);
    ui->mVal->setValue(30);
    ui->nVal->setValue(30);
    ui->RVal->setValue(100);
    ui->rVal->setValue(40);
    ui->xVal->setValidator(new QDoubleValidator());
    ui->yVal->setValidator(new QDoubleValidator());
    ui->zVal->setValidator(new QDoubleValidator());
    ui->xVal->setText("0");
    ui->yVal->setText("0");
    ui->zVal->setText("0");
    ui->opXVal->setValidator(new QDoubleValidator());
    ui->opYVal->setValidator(new QDoubleValidator());
    ui->opZVal->setValidator(new QDoubleValidator());
    ui->opXVal->setText("0");
    ui->opYVal->setText("0");
    ui->opZVal->setText("0");
    ui->alphaAxVal->setValidator(new QDoubleValidator());
    ui->betaAxVal->setValidator(new QDoubleValidator());
    ui->alphaAxVal->setText("45");
    ui->betaAxVal->setText("45");
    ui->alphaOblVal->setValidator(new QDoubleValidator());
    ui->lOblVal->setValidator(new QDoubleValidator());
    ui->alphaOblVal->setText("45");
    ui->lOblVal->setText("1");

    setFixedSize(width(), height());
    m_coordSysCenter.SetX(ui->outputWidget->width() / 2);
    m_coordSysCenter.SetY(ui->outputWidget->height() / 2);
    m_projection = new FrontalProjection();
    m_renderObject = new Thorus();

    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generateObject()));
    connect(ui->translateButton, SIGNAL(clicked()), this, SLOT(translateObject()));
    connect(ui->scaleButton, SIGNAL(clicked()), this, SLOT(scaleObject()));
    connect(ui->rotateButton, SIGNAL(clicked()), this, SLOT(rotateObject()));
    connect(ui->frontalButton, SIGNAL(clicked()), this, SLOT(setFrontalProjection()));
    connect(ui->horizontalButton, SIGNAL(clicked()), this, SLOT(setHorizontalProjection()));
    connect(ui->profileButton, SIGNAL(clicked()), this, SLOT(setProfileProjection()));
    connect(ui->setButton, SIGNAL(clicked()), this, SLOT(setOperationPoint()));
    connect(ui->axonometricButton, SIGNAL(clicked()), this, SLOT(setAxonometricProjection()));
    connect(ui->obliqueButton, SIGNAL(clicked()), this, SLOT(setObliqueProjection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateObject()
{
    static_cast<Thorus*>(m_renderObject)->Construct(ui->nVal->value(), ui->mVal->value(), ui->RVal->value(), ui->rVal->value());
    ui->outputWidget->update();
}

void MainWindow::translateObject()
{
    m_renderObject->Translate(ui->xVal->text().toFloat(), ui->yVal->text().toFloat(), ui->zVal->text().toFloat());
    ui->outputWidget->update();
}

void MainWindow::scaleObject()
{
    m_renderObject->Translate(-m_operationPoint.GetX(), -m_operationPoint.GetY(), -m_operationPoint.GetZ());
    m_renderObject->Scale(ui->xVal->text().toFloat(), ui->yVal->text().toFloat(), ui->zVal->text().toFloat());
    m_renderObject->Translate(m_operationPoint.GetX(), m_operationPoint.GetY(), m_operationPoint.GetZ());
    ui->outputWidget->update();
}

void MainWindow::rotateObject()
{
    m_renderObject->Translate(-m_operationPoint.GetX(), -m_operationPoint.GetY(), -m_operationPoint.GetZ());
    m_renderObject->Rotate(ui->xVal->text().toFloat(), ui->yVal->text().toFloat(), ui->zVal->text().toFloat());
    m_renderObject->Translate(m_operationPoint.GetX(), m_operationPoint.GetY(), m_operationPoint.GetZ());
    ui->outputWidget->update();
}

void MainWindow::setHorizontalProjection()
{
    delete m_projection;
    m_projection = new HorizontalProjection();
    ui->outputWidget->update();
}

void MainWindow::setFrontalProjection()
{
    delete m_projection;
    m_projection = new FrontalProjection();
    ui->outputWidget->update();
}

void MainWindow::setProfileProjection()
{
    delete m_projection;
    m_projection = new ProfileProjection();
    ui->outputWidget->update();
}

void MainWindow::setAxonometricProjection()
{
    delete m_projection;
    m_projection = new AxonometricProjection(ui->alphaAxVal->text().toFloat(), ui->betaAxVal->text().toFloat());
    ui->outputWidget->update();
}

void MainWindow::setObliqueProjection()
{
    delete m_projection;
    m_projection = new ObliqueProjection(ui->alphaOblVal->text().toFloat(), ui->lOblVal->text().toFloat());
    ui->outputWidget->update();
}

void MainWindow::setOperationPoint()
{
    m_operationPoint.SetX(ui->opXVal->text().toFloat());
    m_operationPoint.SetY(ui->opYVal->text().toFloat());
    m_operationPoint.SetZ(ui->opZVal->text().toFloat());
    ui->outputWidget->update();
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (object == ui->outputWidget && event->type() == QEvent::Paint)
    {
        QPainter painter;
        painter.begin(ui->outputWidget);
        drawObject(painter);
        painter.end();
        return true;
    }

    return false;
}

void MainWindow::drawObject(QPainter& painter)
{
    Mesh& objMesh = m_renderObject->GetMesh();
    QList<Point> points = PointsToCoordSystem(m_projection->GetProjectionPoints(objMesh.GetVertices()));
    painter.fillRect(0, 0, width(), height(), Qt::black);
    painter.setPen(Qt::white);
    for (int i = 0; i < objMesh.GetEdgesNum(); i++)
    {
        Edge& edge = objMesh.GetEdge(i);
        painter.drawLine(
                    static_cast<int>(points[edge.vertexIndexes[0]].x),
                    static_cast<int>(points[edge.vertexIndexes[0]].y),
                    static_cast<int>(points[edge.vertexIndexes[1]].x),
                    static_cast<int>(points[edge.vertexIndexes[1]].y));
    }
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    for (int i = 0; i < points.length(); i++)
    {
        painter.drawRect(static_cast<int>(points[i].x) - 1, static_cast<int>(points[i].y) - 1, 2, 2);
    }
    Vertex opCenter;
    opCenter.SetPosition(m_operationPoint.GetX(), m_operationPoint.GetY(), m_operationPoint.GetZ());
    points = PointsToCoordSystem(m_projection->GetProjectionPoints({opCenter}));
    painter.setPen(Qt::yellow);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(static_cast<int>(points[0].x)-5, static_cast<int>(points[0].y)-5, 10, 10);
}

QList<Point> MainWindow::PointsToCoordSystem(const QList<Point>& vertices)
{
    QList<Point> val;
    for(int i = 0; i < vertices.length(); i++)
    {
        Point point;
        point.x = m_coordSysCenter.GetX() + vertices[i].x;
        point.y = m_coordSysCenter.GetY() - vertices[i].y;
        val.push_back(point);
    }
    return val;
}
