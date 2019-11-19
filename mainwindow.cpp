#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/thorus.h"
#include "graphics/projections.h"
#include "widgets/vector3dwidget.h"
#include <QAbstractButton>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(width(), height());

    m_worldWidget = new WorldWidget(ui->outputFrame);
    m_worldWidget->setFixedSize(ui->outputFrame->width(), ui->outputFrame->height());

    m_opPosWidg = new Vector3DWidget(ui->opPosFrame);
    ui->opPosFrame->setLayout(m_opPosWidg->layout());

    m_translateWidg = new Vector3DWidget();
    m_rotateWidg = new Vector3DWidget();
    m_scaleWidg = new Vector3DWidget();
    ui->transformLayout->addWidget(m_translateWidg);
    ui->transformLayout->addWidget(m_rotateWidg);
    ui->transformLayout->addWidget(m_scaleWidg);

    ui->mVal->setRange(3, 50);
    ui->nVal->setRange(3, 50);
    ui->RVal->setRange(1, 1000);
    ui->rVal->setRange(1, 1000);
    ui->mVal->setValue(30);
    ui->nVal->setValue(30);
    ui->RVal->setValue(100);
    ui->rVal->setValue(40);
    ui->alphaAxVal->setValidator(new QDoubleValidator());
    ui->betaAxVal->setValidator(new QDoubleValidator());
    ui->alphaAxVal->setText("45");
    ui->betaAxVal->setText("45");
    ui->alphaOblVal->setValidator(new QDoubleValidator());
    ui->lOblVal->setValidator(new QDoubleValidator());
    ui->alphaOblVal->setText("45");
    ui->lOblVal->setText("1");
    ui->dVal->setValidator(new QDoubleValidator());
    ui->dVal->setText("1");

    connect(ui->generateButton, &QAbstractButton::clicked, this, &MainWindow::generateObject);
    connect(ui->translateButton, &QAbstractButton::clicked, this, &MainWindow::translateObject);
    connect(ui->scaleButton, &QAbstractButton::clicked, this, &MainWindow::scaleObject);
    connect(ui->rotateButton, &QAbstractButton::clicked, this, &MainWindow::rotateObject);
    connect(ui->frontalButton, &QAbstractButton::clicked, this, &MainWindow::setFrontalProjection);
    connect(ui->horizontalButton, &QAbstractButton::clicked, this, &MainWindow::setHorizontalProjection);
    connect(ui->profileButton, &QAbstractButton::clicked, this, &MainWindow::setProfileProjection);
    connect(ui->axonometricButton, &QAbstractButton::clicked, this, &MainWindow::setAxonometricProjection);
    connect(ui->obliqueButton, &QAbstractButton::clicked, this, &MainWindow::setObliqueProjection);
    connect(ui->perspectiveButton, &QAbstractButton::clicked, this, &MainWindow::setPerspectiveProjection);

    Thorus* thorus = static_cast<Thorus*>(&m_worldWidget->GetWorldObject());
    thorus->SetBaseApprox(ui->mVal->value());
    thorus->SetGeneratrixApprox(ui->nVal->value());
    thorus->SetBaseRadius(ui->RVal->value());
    thorus->SetGeneratrixRadius(ui->rVal->value());
    connect(ui->mVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetBaseApprox(int)));
    connect(ui->nVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetGeneratrixApprox(int)));
    connect(ui->RVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetBaseRadius(int)));
    connect(ui->rVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetGeneratrixRadius(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateObject()
{
    Thorus& thorus = static_cast<Thorus&>(m_worldWidget->GetWorldObject());
    thorus.Construct();
    m_worldWidget->update();
}

void MainWindow::translateObject()
{

}

void MainWindow::scaleObject()
{

}

void MainWindow::rotateObject()
{

}

void MainWindow::setHorizontalProjection()
{

}

void MainWindow::setFrontalProjection()
{

}

void MainWindow::setProfileProjection()
{

}

void MainWindow::setAxonometricProjection()
{

}

void MainWindow::setObliqueProjection()
{

}

void MainWindow::setPerspectiveProjection()
{

}

void MainWindow::vc(int a)
{

}
