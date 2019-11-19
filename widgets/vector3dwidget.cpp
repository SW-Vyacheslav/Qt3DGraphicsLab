#include "vector3dwidget.h"
#include <QDoubleValidator>

Vector3DWidget::Vector3DWidget(QWidget *parent) : QWidget(parent)
{
    m_horLay = new QHBoxLayout(this);
    m_labelX = new QLabel();
    m_labelY = new QLabel();
    m_labelZ = new QLabel();
    m_labelX->setText("X:");
    m_labelY->setText("Y:");
    m_labelZ->setText("Z:");
    m_editX = new QLineEdit();
    m_editX->setValidator(new QDoubleValidator());
    m_editX->setText("0");
    m_editY = new QLineEdit();
    m_editY->setValidator(new QDoubleValidator());
    m_editY->setText("0");
    m_editZ = new QLineEdit();
    m_editZ->setValidator(new QDoubleValidator());
    m_editZ->setText("0");
    m_horLay->addWidget(m_labelX);
    m_horLay->addWidget(m_editX);
    m_horLay->addWidget(m_labelY);
    m_horLay->addWidget(m_editY);
    m_horLay->addWidget(m_labelZ);
    m_horLay->addWidget(m_editZ);
    connect(m_editX, &QLineEdit::editingFinished, this, &Vector3DWidget::EditXChanged);
    connect(m_editY, &QLineEdit::editingFinished, this, &Vector3DWidget::EditYChanged);
    connect(m_editZ, &QLineEdit::editingFinished, this, &Vector3DWidget::EditZChanged);
    setLayout(m_horLay);
}

Vector3DWidget::~Vector3DWidget()
{
    delete m_editX;
    delete m_editY;
    delete m_editZ;
    delete m_labelX;
    delete m_labelY;
    delete m_labelZ;
}

Vector3D Vector3DWidget::GetValue() const
{
    return m_value;
}

void Vector3DWidget::SetValue(const Vector3D &value)
{
    m_value = value;
    emit OnValueChanged(m_value);
}

void Vector3DWidget::EditXChanged()
{
    m_value.SetX(m_editX->text().toFloat());
    emit OnValueChanged(m_value);
}

void Vector3DWidget::EditYChanged()
{
    m_value.SetY(m_editY->text().toFloat());
    emit OnValueChanged(m_value);
}

void Vector3DWidget::EditZChanged()
{
    m_value.SetZ(m_editZ->text().toFloat());
    emit OnValueChanged(m_value);
}
