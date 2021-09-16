#include "enemytank.h"

EnemyTank::EnemyTank(int widthBlock, QObject *parent) : QObject(parent),
    QGraphicsPixmapItem(QPixmap(":/images/tank1up.png").scaled(widthBlock, widthBlock)),
    mWidthBlock(widthBlock)
{

}

void EnemyTank::advance(int phase)
{
    if (phase) {
        if (data(5) == true) {
            spawnScore();
            delete this;
            return;
        }
    }
}

void EnemyTank::spawnScore()
{
    Score *score = new Score();
    scene()->addItem(score);
    score->setPos(scenePos());
    score->startAnimation();
}
