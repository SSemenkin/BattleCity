#include "shield.h"

Shield::Shield(QGraphicsItem *item, int pixmapWidth) :
    Entity(QPixmap(":/images/shield/shield1.png").scaled(pixmapWidth, pixmapWidth), item),
    m_blinkTimer(new QTimer(this)),
    m_remainingTimer(new QTimer(this))
{
    QObject::connect(m_remainingTimer, &QTimer::timeout, this, [this](){
        setRequireToDestroy();
    });
    QObject::connect(m_blinkTimer, &QTimer::timeout, this, &Shield::swapPixmaps);

    m_blinkTimer->start(SWAP_PIXMAPS_DELTA);
    m_remainingTimer->start(BONUS_DURATION);
}

void Shield::resetTimer()
{
    m_remainingTimer->stop();
    m_remainingTimer->start(BONUS_DURATION);
}

void Shield::swapPixmaps()
{
    m_swapRequire ? setPixmap(QPixmap(":/images/shield/shield2.png").scaled(pixmap().width(), pixmap().height())):
                    setPixmap(QPixmap(":/images/shield/shield1.png").scaled(pixmap().width(), pixmap().height()));
    m_swapRequire = !m_swapRequire;
}
