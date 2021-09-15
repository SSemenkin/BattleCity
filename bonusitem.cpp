#include "bonusitem.h"

BonusItem::BonusItem(Type type, int sideWidth, QGraphicsItem *parent, QObject *objectParent)
    : QObject(objectParent),
    QGraphicsPixmapItem(parent)
{
    setZValue(3);

    switch(type) {
        case Type::Granade:
        {
            setPixmap(QPixmap(":/images/bonus/granade.png").scaled(sideWidth, sideWidth));
            break;
        }
        case Type::Helmet:
        {
            setPixmap(QPixmap(":/images/bonus/helmet.png").scaled(sideWidth, sideWidth));
            break;
        }
        case Type::Shovel:
        {
            setPixmap(QPixmap(":/images/bonus/shovel.png").scaled(sideWidth, sideWidth));
            break;
        }
        case Type::Star:
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
        delete this;
    }
}
