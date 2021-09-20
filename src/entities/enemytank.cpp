#include "enemytank.h"

EnemyTank::EnemyTank(int pixmapWidth) :
    Tank(QPixmap(":/images/tank1up.png").scaled(pixmapWidth, pixmapWidth)),
    m_directionTimer(new QTimer(this)),
    m_shootTimer(new QTimer(this))
{
    m_speed = TANK_SPEED;
    setLivesLeft(1);

    QObject::connect(m_directionTimer, &QTimer::timeout, this, &EnemyTank::changeDirection);
    QObject::connect(m_shootTimer,     &QTimer::timeout, this, &Tank::shoot);

    m_directionTimer->start(1000);
    m_shootTimer->start(1000);
}

void EnemyTank::changeDirection()
{
    int value = rand() % 4;
    Qt::Key key = Qt::Key_Up;
    switch(value) {
        case 0:
        {
            key = Qt::Key_Up;
            break;
        }
        case 1:
        {
            key = Qt::Key_Down;
            break;
        }
        case 2:
        {
            key = Qt::Key_Left;
            break;
        }
        case 3:
        {
            key = Qt::Key_Right;
            break;
        }
    }

    m_direction = getNewDirection(key);
}
