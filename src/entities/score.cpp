#include "score.h"

Score::Score(int pixmapWidth) :
    Entity(QPixmap(":/images/100point.png").scaled(pixmapWidth/2, pixmapWidth/2)),
    m_remainingTimer(new QTimer(this))
{
    setDestructible(false);
    setBulletCanMoveThroughObject(true);
    setActorCanMoveThroughObject(true);
    setZValue(3);
    QObject::connect(m_remainingTimer, &QTimer::timeout, this, [this]()->void {
        setRequireToDestroy();
    });
    m_remainingTimer->start(SCORE_DURATION);
}

void Score::advance(int phase)
{
    if (phase) {
        moveBy(1, -1);
        Entity::advance(phase);
    }
}
