#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QTimer>

#include "entities/entity.h"

class Explosion : public Entity
{
    Q_OBJECT
public:
    explicit Explosion(const QPointF &fixedCenter, int pixmapWidth);
    void startAnimation();

private:
    QVector<QPixmap> m_frames;
    int m_frame {0};
    int m_pixmapWidth;
    QTimer *m_frameTimer;
    QPointF m_center;

private:
    void changePixmap();
};

#endif // EXPLOSION_H
