#include "bonusitem.h"

BonusItem::BonusItem(BonusType type, int sideWidth, QGraphicsItem *parent, QObject *objectParent)
    : QObject(objectParent),
    QGraphicsPixmapItem(parent),
    mType(type),
    mRemainingTimer(new QTimer(this)),
    mSwapTimer(new QTimer(this))
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
    mPixmap = pixmap();
    setData(0, "Bonus");
    setData(1, static_cast<int>(type));
    setData(5, false); // on destroy
    QObject::connect(mRemainingTimer, &QTimer::timeout, this, [this] () {
        mRemainingTimer->stop();
        QObject::connect(mSwapTimer, &QTimer::timeout, this, [this] () {
           mSwap ? setPixmap(QPixmap()) :
                   setPixmap(mPixmap);
           mSwap = !mSwap;
           if (calls++ == 20) {
               mSwapTimer->stop();
               delete this;
           }
        });
        mSwapTimer->start(150);
        delete mRemainingTimer;
    });
    mRemainingTimer->start(15000);// 15 seconds
}

void BonusItem::advance(int phase)
{
    if (phase && data(5).toBool()) {
        emit picked(mType);
        delete this;
    }
}
