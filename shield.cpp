﻿#include "shield.h"

Shield::Shield(QGraphicsPixmapItem *player, QObject *parent) :
    QObject(parent),
    QGraphicsPixmapItem(QPixmap(":/images/shield/shield1.png"), player),
    mChangeTimer(new QTimer(this))
{
    setZValue(1);
    setData(0, "Bonus");
    QObject::connect(mChangeTimer, &QTimer::timeout, this, [this] () {
       swapImage ? setPixmap(QPixmap(":/images/shield/shield2.png")) :
                   setPixmap(QPixmap(":/images/shield/shield1.png"));
       swapImage = !swapImage;
       if (calls++ == 50) {
           parentItem()->setData(2, false);
           delete this;
       }
    });
    QObject::connect(qgraphicsitem_cast<Player*>(player), &Player::refreshTimer, this, [this] () {
       calls = 0;
    });
    mChangeTimer->start(150);
}
