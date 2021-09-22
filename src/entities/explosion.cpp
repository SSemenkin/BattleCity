#include "explosion.h"

Explosion::Explosion(const QPointF& fixedCenter, int pixmapWidth) :
    m_pixmapWidth(pixmapWidth),
    m_center(fixedCenter)
{
    setDestructible(false);
    setBulletCanMoveThroughObject(true);
    setActorCanMoveThroughObject(true);
    setLivesLeft(1);
    setZValue(3);


    m_frames = {
        QPixmap(":/images/explosion/explosion1.png"),
        QPixmap(":/images/explosion/explosion2.png"),
        QPixmap(":/images/explosion/explosion3.png"),
        QPixmap(":/images/explosion/explosion4.png"),
        QPixmap(":/images/explosion/explosion5.png")
    };
    changePixmap();
}

void Explosion::startAnimation()
{
    m_frameTimer = new QTimer(this);
    QObject::connect(m_frameTimer, &QTimer::timeout, this, &Explosion::changePixmap);
    m_frameTimer->start(SWAP_PIXMAPS_DELTA/2);
}

void Explosion::changePixmap()
{
    setPixmap(m_frames.at(m_frame++).scaled(m_pixmapWidth, m_pixmapWidth));
    setPos(m_center.x() - pixmap().height(),
           m_center.y() - pixmap().width());
    if (m_frame == m_frames.size()) {
        m_frameTimer->stop();
        setRequireToDestroy();
    }
}
