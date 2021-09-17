#include "shield.h"

Shield::Shield(QGraphicsItem *player, int block, QObject *parent) :
    QObject(parent),
    QGraphicsPixmapItem(QPixmap(":/images/shield/shield1.png").scaled(block, block), player),
    mChangeTimer(new QTimer(this))
{
    setZValue(1);
    setData(0, "Bonus");
    QObject::connect(mChangeTimer, &QTimer::timeout, this, [this] () {
       swapImage ? setPixmap(QPixmap(":/images/shield/shield2.png").scaled(pixmap().size())) :
                   setPixmap(QPixmap(":/images/shield/shield1.png").scaled(pixmap().size()));
       swapImage = !swapImage;
       if (calls++ == 50) {
           parentItem()->setData(2, false);
           delete this;
       }
    });

    mChangeTimer->start(150);
}
