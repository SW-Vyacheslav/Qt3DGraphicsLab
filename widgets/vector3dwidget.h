#ifndef VECTOR3DWIDGET_H
#define VECTOR3DWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "math/Vector3D.h"

class Vector3DWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Vector3DWidget(QWidget *parent = nullptr);
    ~Vector3DWidget();

    Vector3D GetValue() const;

signals:
    void OnValueChanged(const Vector3D& value);

public slots:
    void SetValue(const Vector3D& value);

private slots:
    void EditXChanged();
    void EditYChanged();
    void EditZChanged();

private:
    Vector3D m_value;
    QHBoxLayout* m_horLay;
    QLineEdit* m_editX;
    QLineEdit* m_editY;
    QLineEdit* m_editZ;
    QLabel* m_labelX;
    QLabel* m_labelY;
    QLabel* m_labelZ;
};

#endif // VECTOR3DWIDGET_H
