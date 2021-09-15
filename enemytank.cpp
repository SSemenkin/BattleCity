#include "enemytank.h"

EnemyTank::EnemyTank(QObject *parent) : QObject(parent),
    QGraphicsPixmapItem(QPixmap(":/images/tank1up.png"))
{

}
