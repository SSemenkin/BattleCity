#include "enemytank.h"

int EnemyTank::CHANGE_DIRECTION_DELTA = 1000; // 1 seconds;
int EnemyTank::FIRE_DELTA = CHANGE_DIRECTION_DELTA;

EnemyTank::EnemyTank(int widthBlock, QObject *parent) :
    GraphicsPixmapObject(QPixmap(":/images/tank1up.png").scaled(widthBlock, widthBlock), nullptr, parent),
    mWidthBlock(widthBlock),
    mDirectionTimer(new QTimer(this)),
    mFireTimer(new QTimer(this))
{
    setData(0, "Enemy");
    CURRENT_SPEED = PLAYER_MAX_SPEED;
    changeDirection();

    QObject::connect(mDirectionTimer, &QTimer::timeout, this, &EnemyTank::changeDirection);
    QObject::connect(mFireTimer, &QTimer::timeout, this, &EnemyTank::fire);

    mDirectionTimer->start(CHANGE_DIRECTION_DELTA);
    mFireTimer->start(FIRE_DELTA);
}

void EnemyTank::advance(int phase)
{
    GraphicsPixmapObject::advance(phase);
    if (data(5).toBool()) {
        spawnScore();
        delete this;
    }
}


void EnemyTank::spawnScore()
{
    Score *score = new Score();
    scene()->addItem(score);
    score->setPos(scenePos());
    score->startAnimation();
}

void EnemyTank::changeDirection()
{
    int key = rand() % 4;

    switch(key) {
    case 0:
        key = Qt::Key_Left;
        break;
    case 1:
        key = Qt::Key_Right;
        break;
    case 2:
        key = Qt::Key_Up;
        break;
    case 3:
        key = Qt::Key_Down;
        break;
    }

    mDirection = newDirection(static_cast<Qt::Key>(key));
}
