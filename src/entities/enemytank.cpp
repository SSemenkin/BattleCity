#include "enemytank.h"

QSound EnemyTank::destroy_sound("qrc:/sounds/explosion.wav");

EnemyTank::EnemyTank(int pixmapWidth) :
    Tank(QPixmap(":/images/tank1up.png").scaled(pixmapWidth, pixmapWidth)),
    m_directionTimer(new QTimer(this)),
    m_shootTimer(new QTimer(this))
{
    bool r = rand() & 1;
    if (r) {
        setPixmap(QPixmap(":/images/tank2up.png").scaled(pixmapWidth, pixmapWidth));
        m_speed = TANK_SPEED;
        setLivesLeft(1);
    } else {
        m_speed = TANK_SPEED * 2;
        setLivesLeft(2);
    }
    changeDirection();

    setEntityName("Enemy");

    QObject::connect(m_directionTimer, &QTimer::timeout, this, &EnemyTank::changeDirection);
    QObject::connect(m_shootTimer,     &QTimer::timeout, this, &Tank::shoot);

    m_directionTimer->start(ENEMY_SWAP_DIRECTION_DELTA);
    m_shootTimer->start(ENEMY_SHOOT_DELTA);
}

EnemyTank::~EnemyTank()
{
    destroy_sound.play();
}

void EnemyTank::advance(int phase)
{
    if (phase) {
        if (isRequireToDestroy()) {
            Score *score = new Score(pixmap().width());
            scene()->addItem(score);
            score->setPos(scenePos());
        }
        Tank::advance(phase);
    }
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
