#include "bonusitem.h"

BonusItem::BonusItem(BonusType type, int sideWidth, QGraphicsItem *parent, QObject *objectParent)
    : QObject(objectParent),
    QGraphicsPixmapItem(parent),
    mType(type)
{
    setZValue(3);

    switch(type) {
        case BonusType::Granade:
        {
            setPixmap(QPixmap(":/images/bonus/granade.png").scaled(sideWidth, sideWidth));
            break;
        }
        case BonusType::Helmet:
        {
            setPixmap(QPixmap(":/images/bonus/helmet.png").scaled(sideWidth, sideWidth));
            break;
        }
        case BonusType::Shovel:
        {
            setPixmap(QPixmap(":/images/bonus/shovel.png").scaled(sideWidth, sideWidth));
            break;
        }
        case BonusType::Star:
        {
            setPixmap(QPixmap(":/images/bonus/star.png").scaled(sideWidth, sideWidth));
            break;
        }
    }
    setData(0, "Bonus");
    setData(1, static_cast<int>(type));
    setData(5, false); // on destroy
}

void BonusItem::advance(int phase)
{
    if (phase && data(5).toBool()) {
        emit picked(mType);
        delete this;
    }
}
