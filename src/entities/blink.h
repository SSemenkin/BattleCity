#ifndef BLINK_H
#define BLINK_H

#include <QTimer>

#include "entities/enemytank.h"

class Blink : public Entity
{
    Q_OBJECT
public:
    explicit Blink(int pixmapWidth);
    void startAnimation();

private:
    QTimer *m_framesTimer;

    int m_frame {0};
    int m_pixmapWidth;

    QVector<QPixmap> m_frames;

private:
    void changePixmap();
    void createEnemyTank();

};

#endif // BLINK_H
