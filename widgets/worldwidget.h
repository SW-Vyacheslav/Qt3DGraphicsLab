#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>
#include "graphics/components/worldobject.h"
#include "graphics/components/camera.h"

class WorldWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WorldWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

private:
    WorldObject* m_worldObject;
    Camera* m_camera;
};

#endif // WORLDWIDGET_H
