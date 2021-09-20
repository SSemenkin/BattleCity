#include "blink.h"


Blink::Blink(int pixmapWidth) :
    m_pixmapWidth(pixmapWidth)
{
    setDestructible(false);
    setBulletCanMoveThroughObject(true);
    setActorCanMoveThroughObject(false);
    m_frames = {
        QPixmap(":/images/blink/blink1.png"),
        QPixmap(":/images/blink/blink2.png"),
        QPixmap(":/images/blink/blink3.png"),
        QPixmap(":/images/blink/blink4.png")
    };

    changePixmap();
}

void Blink::startAnimation()
{
    m_framesTimer = new QTimer(this);
    QObject::connect(m_framesTimer, &QTimer::timeout, this, &Blink::changePixmap);
    m_framesTimer->start(150);
}

void Blink::changePixmap()
{
    setPixmap(m_frames.at(m_frame++).scaled(m_pixmapWidth, m_pixmapWidth));
    if (m_frame == m_frames.size()) {
        m_framesTimer->stop();
        createEnemyTank();
        setRequireToDestroy();
    }
}

void Blink::createEnemyTank()
{
    EnemyTank *enemy = new EnemyTank(m_pixmapWidth);
    enemy->setBorderPoint(borderPoint());
    scene()->addItem(enemy);
    enemy->setPos(scenePos());
}
