#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphics/projections.h"
#include "widgets/vector3dwidget.h"
#include <QAbstractButton>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(width(), height());
    ui->opPosGroupBox->hide();

    m_worldWidget = new WorldWidget(ui->outputFrame);
    m_worldWidget->setFixedSize(ui->outputFrame->size());

    m_opPosWidg = new Vector3DWidget(ui->opPosFrame);
    ui->opPosFrame->setLayout(m_opPosWidg->layout());
    connect(m_opPosWidg, &Vector3DWidget::OnValueChanged, &m_worldWidget->GetWorldObject().GetTransform(), &Transform::SetOpPosition);

    m_lightWidg = new Vector3DWidget();
    ui->lightFrame->setLayout(m_lightWidg->layout());
    connect(m_lightWidg, &Vector3DWidget::OnValueChanged, m_worldWidget, &WorldWidget::SetLight);

    m_translateWidg = new Vector3DWidget();
    ui->translateFrame->setLayout(m_translateWidg->layout());
    m_rotateWidg = new Vector3DWidget();
    ui->rotateFrame->setLayout(m_rotateWidg->layout());
    m_scaleWidg = new Vector3DWidget();
    ui->scaleFrame->setLayout(m_scaleWidg->layout());

    m_transfPosWidg = new Vector3DWidget();
    ui->positionFrame->setLayout(m_transfPosWidg->layout());
    connect(m_transfPosWidg, &Vector3DWidget::OnValueChanged, &m_worldWidget->GetWorldObject().GetTransform(), &Transform::SetPosition);
    m_transfRotWidg = new Vector3DWidget();
    ui->rotationFrame->setLayout(m_transfRotWidg->layout());
    connect(m_transfRotWidg, &Vector3DWidget::OnValueChanged, &m_worldWidget->GetWorldObject().GetTransform(), &Transform::SetRotation);
    m_transfScaleWidg = new Vector3DWidget();
    ui->scaleFrame2->setLayout(m_transfScaleWidg->layout());
    connect(m_transfScaleWidg, &Vector3DWidget::OnValueChanged, &m_worldWidget->GetWorldObject().GetTransform(), &Transform::SetScale);

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
    ui->roVal->setValidator(new QDoubleValidator());
    ui->roVal->setText("1");
    ui->alphaPerVal->setValidator(new QDoubleValidator());
    ui->alphaPerVal->setText("0");
    ui->betaPerVal->setValidator(new QDoubleValidator());
    ui->betaPerVal->setText("0");

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
    connect(ui->wireframeRadioButton, &QRadioButton::clicked, this, &MainWindow::drawModelChanged);
    connect(ui->surfaceRadioButton, &QRadioButton::clicked, this, &MainWindow::drawModelChanged);

    Thorus* thorus = static_cast<Thorus*>(&m_worldWidget->GetWorldObject());
    thorus->SetBaseApprox(ui->mVal->value());
    thorus->SetGeneratrixApprox(ui->nVal->value());
    thorus->SetBaseRadius(ui->RVal->value());
    thorus->SetGeneratrixRadius(ui->rVal->value());
    connect(ui->mVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetBaseApprox(int)));
    connect(ui->nVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetGeneratrixApprox(int)));
    connect(ui->RVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetBaseRadius(int)));
    connect(ui->rVal, SIGNAL(valueChanged(int)), thorus, SLOT(SetGeneratrixRadius(int)));

    updateTransformWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Thorus &MainWindow::getThorus()
{
    return static_cast<Thorus&>(m_worldWidget->GetWorldObject());
}

void MainWindow::updateTransformWidgets()
{
    Transform& transform = m_worldWidget->GetWorldObject().GetTransform();
    m_transfPosWidg->SetValue(transform.GetPosition());
    m_transfRotWidg->SetValue(transform.GetRotation());
    m_transfScaleWidg->SetValue(transform.GetScale());
}

void MainWindow::closeEvent(QCloseEvent*)
{
    exit(1);
}

void MainWindow::generateObject()
{
    Thorus& thorus = getThorus();
    thorus.Construct();
    m_worldWidget->redraw();
    updateTransformWidgets();
}

void MainWindow::translateObject()
{
    Vector3D val = m_translateWidg->GetValue();
    m_worldWidget->GetWorldObject().GetTransform().Translate(val.GetX(), val.GetY(), val.GetZ());
    updateTransformWidgets();
}

void MainWindow::scaleObject()
{
    Vector3D val = m_scaleWidg->GetValue();
    m_worldWidget->GetWorldObject().GetTransform().Scale(val.GetX(), val.GetY(), val.GetZ());
    updateTransformWidgets();
}

void MainWindow::rotateObject()
{
    Vector3D val = m_rotateWidg->GetValue();
    m_worldWidget->GetWorldObject().GetTransform().Rotate(val.GetX(), val.GetY(), val.GetZ());
    updateTransformWidgets();
}

void MainWindow::setHorizontalProjection()
{
    m_worldWidget->SetProjection(new HorizontalProjection());
}

void MainWindow::setFrontalProjection()
{
    m_worldWidget->SetProjection(new FrontalProjection());
}

void MainWindow::setProfileProjection()
{
    m_worldWidget->SetProjection(new ProfileProjection());
}

void MainWindow::setAxonometricProjection()
{
    float alpha = ui->alphaAxVal->text().toFloat();
    float beta = ui->betaAxVal->text().toFloat();
    m_worldWidget->SetProjection(new AxonometricProjection(alpha, beta));
}

void MainWindow::setObliqueProjection()
{
    float alpha = ui->alphaOblVal->text().toFloat();
    float lVal = ui->lOblVal->text().toFloat();
    m_worldWidget->SetProjection(new ObliqueProjection(alpha, lVal));
}

void MainWindow::setPerspectiveProjection()
{
    float dVal = ui->dVal->text().toFloat();
    float roVal = ui->roVal->text().toFloat();
    float alpha = ui->alphaPerVal->text().toFloat();
    float beta = ui->betaPerVal->text().toFloat();
    m_worldWidget->SetProjection(new PerspectiveProjection(dVal, roVal, alpha, beta));
}

void MainWindow::drawModelChanged()
{
    if (ui->wireframeRadioButton->isChecked())
        m_worldWidget->SetDrawModel(WorldWidget::WIREFRAME);
    else if (ui->surfaceRadioButton->isChecked())
        m_worldWidget->SetDrawModel(WorldWidget::SURFACE);
}
