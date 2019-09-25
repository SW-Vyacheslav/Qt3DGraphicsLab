#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/vertex.h"
#include "graphics/mesh.h"
#include "QPainter"
#include "graphics/frontalprojection.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->outputWidget->installEventFilter(this);
    ui->mVal->setValue(25);
    ui->nVal->setValue(25);
    ui->RVal->setValue(70);
    ui->rVal->setValue(30);

    ui->xVal->setValidator(new QDoubleValidator());
    ui->yVal->setValidator(new QDoubleValidator());
    ui->zVal->setValidator(new QDoubleValidator());
    ui->xVal->setText("0");
    ui->yVal->setText("0");
    ui->zVal->setText("0");

    setFixedSize(width(), height());
    m_isUpdate = false;
    m_coordSysCenter.SetX(ui->outputWidget->width()/2);
    m_coordSysCenter.SetY(ui->outputWidget->height()/2);
    m_projection = new FrontalProjection();

    connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generateObject()));
    connect(ui->translateButton, SIGNAL(clicked()), this, SLOT(translateObject()));
    connect(ui->scaleButton, SIGNAL(clicked()), this, SLOT(scaleObject()));
    connect(ui->rotateButton, SIGNAL(clicked()), this, SLOT(rotateObject()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateObject()
{
    m_isUpdate = true;
    m_thorus.Construct(ui->nVal->value(), ui->mVal->value(), ui->RVal->value(), ui->rVal->value());
    ui->outputWidget->update();
}

void MainWindow::translateObject()
{
    m_isUpdate = true;
    m_thorus.Translate(ui->xVal->text().toFloat(), ui->yVal->text().toFloat(), ui->zVal->text().toFloat());
    ui->outputWidget->update();
}

void MainWindow::scaleObject()
{
    m_isUpdate = true;
    m_thorus.Scale(ui->xVal->text().toFloat(), ui->yVal->text().toFloat(), ui->zVal->text().toFloat());
    ui->outputWidget->update();
}

void MainWindow::rotateObject()
{
    m_isUpdate = true;
    m_thorus.Rotate(ui->xVal->text().toFloat(), ui->yVal->text().toFloat(), ui->zVal->text().toFloat());
    ui->outputWidget->update();
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->outputWidget && event->type() == QEvent::Paint && m_isUpdate)
    {
        QPainter painter;
        painter.begin(ui->outputWidget);
        drawObject(painter);
        painter.end();
        m_isUpdate = false;
        return true;
    }
    return false;
}

void MainWindow::drawObject(QPainter& painter)
{
    Mesh& objMesh = m_thorus.GetMesh();
    QList<QPointF> points = PointsToCoordSystem(m_projection->GetProjectionPoints(objMesh.GetVertices()));

    for (int i = 0; i < points.length(); i++)
    {
        painter.drawPoint(static_cast<int>(points[i].x()), static_cast<int>(points[i].y()));
    }
}

QList<QPointF> MainWindow::PointsToCoordSystem(const QList<QPointF>& vertices)
{
    QList<QPointF> val;
    for(int i = 0; i < vertices.length(); i++)
    {
        QPointF point;
        point.setX(static_cast<double>(m_coordSysCenter.GetX()) + vertices[i].x());
        point.setY(static_cast<double>(m_coordSysCenter.GetY()) - vertices[i].y());
        val.push_back(point);
    }

    return val;
}
