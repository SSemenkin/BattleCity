#include "bonus.h"

Bonus::Bonus(int pixmapWidth, QGraphicsItem *parent) :
    Entity(QPixmap(), parent),
    m_frameTimer(new QTimer(this)),
    m_remainingTimer(new QTimer(this)),
    m_pixmapWidth(pixmapWidth)
{
    init();
    m_pixmap = pixmap();
    QObject::connect(m_remainingTimer, &QTimer::timeout, this, [this]()->void{
        setRequireToDestroy();
    });
    QObject::connect(m_frameTimer, &QTimer::timeout, this, &Bonus::resetTimer);
    m_frameTimer->start(BONUS_DURATION - 2000);
    m_remainingTimer->start(BONUS_DURATION);
}

void Bonus::advance(int phase)
{
    if (phase) {
        if (isPicked()) {
            emit picked(m_type);
            setRequireToDestroy();
        }
        Entity::advance(phase);
    }
}

void Bonus::changePixmap()
{
    m_requireSwap ? setPixmap(QPixmap()):
                    setPixmap(m_pixmap);
    m_requireSwap = !m_requireSwap;
}

void Bonus::resetTimer()
{
    m_frameTimer->stop();
    QObject::disconnect(m_frameTimer, &QTimer::timeout, this, &Bonus::resetTimer);
    QObject::connect(m_frameTimer, &QTimer::timeout, this, &Bonus::changePixmap);
    m_frameTimer->start(SWAP_PIXMAPS_DELTA);
}

void Bonus::init()
{
    setDestructible(false);
    setBulletCanMoveThroughObject(true);
    setActorCanMoveThroughObject(true);
    setLivesLeft(1);
    setEntityName("Bonus");


    m_type = static_cast<Type>(rand() % 4);

    switch(m_type) {
        case Type::Granade:
        {
            setPixmap(QPixmap(":/images/bonus/granade.png"));
            break;
        }
        case Type::Shield:
        {
            setPixmap(QPixmap(":/images/bonus/helmet.png"));
            break;
        }
        case Type::Shovel:
        {
            setPixmap(QPixmap(":/images/bonus/shovel.png"));
            break;
        }
        case Type::Star:
        {
            setPixmap(QPixmap(":/images/bonus/star.png"));
            break;
        }
    }
    setPixmap(pixmap().scaled(m_pixmapWidth, m_pixmapWidth));
}
