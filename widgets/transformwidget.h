#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>
#include "widgets/vector3dwidget.h"
#include "graphics/components/transform.h"

class TransformWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransformWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    Transform m_transform;
    Vector3DWidget m_posWidg;
    Vector3DWidget m_rotWidg;
    Vector3DWidget m_scaleWidg;
};

#endif // TRANSFORMWIDGET_H
