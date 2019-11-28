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

    connect(ui->arSlider, &QSlider::valueChanged, this, &MainWindow::ambientLightValueChanged);
    connect(ui->agSlider, &QSlider::valueChanged, this, &MainWindow::ambientLightValueChanged);
    connect(ui->abSlider, &QSlider::valueChanged, this, &MainWindow::ambientLightValueChanged);
    connect(ui->amrSlider, &QSlider::valueChanged, this, &MainWindow::ambientLightValueChanged);
    connect(ui->drSlider, &QSlider::valueChanged, this, &MainWindow::diffuseLightValueChanged);
    connect(ui->dgSlider, &QSlider::valueChanged, this, &MainWindow::diffuseLightValueChanged);
    connect(ui->dbSlider, &QSlider::valueChanged, this, &MainWindow::diffuseLightValueChanged);
    connect(ui->dmrSlider, &QSlider::valueChanged, this, &MainWindow::diffuseLightValueChanged);
    connect(ui->srSlider, &QSlider::valueChanged, this, &MainWindow::specularLightValueChanged);
    connect(ui->sgSlider, &QSlider::valueChanged, this, &MainWindow::specularLightValueChanged);
    connect(ui->sbSlider, &QSlider::valueChanged, this, &MainWindow::specularLightValueChanged);
    connect(ui->smrSlider, &QSlider::valueChanged, this, &MainWindow::specularLightValueChanged);
    connect(ui->shininessSlider, &QSlider::valueChanged, this, &MainWindow::specularLightValueChanged);

    connect(ui->arSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->agSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->abSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->amrSlider, &QSlider::sliderReleased,m_worldWidget, &WorldWidget::redraw);
    connect(ui->drSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->dgSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->dbSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->dmrSlider, &QSlider::sliderReleased,m_worldWidget, &WorldWidget::redraw);
    connect(ui->srSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->sgSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->sbSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);
    connect(ui->smrSlider, &QSlider::sliderReleased,m_worldWidget, &WorldWidget::redraw);
    connect(ui->shininessSlider, &QSlider::sliderReleased, m_worldWidget, &WorldWidget::redraw);

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

void MainWindow::ambientLightValueChanged(int)
{
    float rVal = ui->arSlider->value() / 100.0f;
    float gVal = ui->agSlider->value() / 100.0f;
    float bVal = ui->abSlider->value() / 100.0f;
    float mrVal = ui->amrSlider->value() / 100.0f;

    ColorN color;
    color.setRed(rVal);
    color.setGreen(gVal);
    color.setBlue(bVal);

    ColorN reflect;
    reflect.setRed(mrVal);
    reflect.setGreen(mrVal);
    reflect.setBlue(mrVal);

    m_worldWidget->SetAmbientColor(color);
    m_worldWidget->SetAmbientMaterialReflection(reflect);

    ui->arLabel->setText(QString::number(static_cast<double>(rVal)));
    ui->agLabel->setText(QString::number(static_cast<double>(gVal)));
    ui->abLabel->setText(QString::number(static_cast<double>(bVal)));
    ui->amrLabel->setText(QString::number(static_cast<double>(mrVal)));
}

void MainWindow::diffuseLightValueChanged(int)
{
    float rVal = ui->drSlider->value() / 100.0f;
    float gVal = ui->dgSlider->value() / 100.0f;
    float bVal = ui->dbSlider->value() / 100.0f;
    float mrVal = ui->dmrSlider->value() / 100.0f;

    ColorN color;
    color.setRed(rVal);
    color.setGreen(gVal);
    color.setBlue(bVal);

    ColorN reflect;
    reflect.setRed(mrVal);
    reflect.setGreen(mrVal);
    reflect.setBlue(mrVal);

    m_worldWidget->SetDiffuseColor(color);
    m_worldWidget->SetDiffuseMaterialReflection(reflect);

    ui->drLabel->setText(QString::number(static_cast<double>(rVal)));
    ui->dgLabel->setText(QString::number(static_cast<double>(gVal)));
    ui->dbLabel->setText(QString::number(static_cast<double>(bVal)));
    ui->dmrLabel->setText(QString::number(static_cast<double>(mrVal)));
}

void MainWindow::specularLightValueChanged(int)
{
    float rVal = ui->srSlider->value() / 100.0f;
    float gVal = ui->sgSlider->value() / 100.0f;
    float bVal = ui->sbSlider->value() / 100.0f;
    float mrVal = ui->smrSlider->value() / 100.0f;
    int shininessVal = ui->shininessSlider->value();

    ColorN color;
    color.setRed(rVal);
    color.setGreen(gVal);
    color.setBlue(bVal);

    ColorN reflect;
    reflect.setRed(mrVal);
    reflect.setGreen(mrVal);
    reflect.setBlue(mrVal);

    m_worldWidget->SetSpecularColor(color);
    m_worldWidget->SetSpecularMaterialReflection(reflect);
    m_worldWidget->SetShininess(shininessVal);

    ui->srLabel->setText(QString::number(static_cast<double>(rVal)));
    ui->sgLabel->setText(QString::number(static_cast<double>(gVal)));
    ui->sbLabel->setText(QString::number(static_cast<double>(bVal)));
    ui->smrLabel->setText(QString::number(static_cast<double>(mrVal)));
    ui->shininessLabel->setText(QString::number(shininessVal));
}
