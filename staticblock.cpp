#include "staticblock.h"


StaticBlock::StaticBlock(Type type, int blockSide, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    switch (type) {
        case Type::Brick:
        {
            setPixmap(QPixmap(":/images/static_blocks/brick.png").scaled(blockSide, blockSide));
            mTankSpeed = 0;
            mHealth = 1;
            mDestructible = true;
            mPerforating = false;
            break;
        }
        case Type::Bush:
        {
            setZValue(2);
            setPixmap(QPixmap(":/images/static_blocks/bush.png").scaled(blockSide, blockSide));
            mTankSpeed = 2;
            mHealth = 1;
            mDestructible = false;
            mPerforating = true;
            break;
        }
        case Type::Concrete:
        {
            setPixmap(QPixmap(":/images/static_blocks/concrete.png").scaled(blockSide, blockSide));
            mTankSpeed = 0;
            mHealth = 2;
            mDestructible = true;
            mPerforating = false;
            break;
        }
        case Type::Water:
        {
            setPixmap(QPixmap(":/images/static_blocks/water1.png").scaled(blockSide, blockSide));
            mWaterTimer = new QTimer(this);
            connect(mWaterTimer, &QTimer::timeout, this, [this, blockSide] () {
               swapWater ?
                            setPixmap(QPixmap(":/images/static_blocks/water2.png").scaled(blockSide, blockSide)):
                            setPixmap(QPixmap(":/images/static_blocks/water1.png").scaled(blockSide, blockSide));
               swapWater = !swapWater;
            });
            mWaterTimer->start(200);
            mTankSpeed = 1;
            mHealth = 1;
            mDestructible = false;
            mPerforating = true;
            break;
        }
    }

    setData(0, "StaticBody");
    setData(1, mPerforating);
    setData(2, mDestructible);
    setData(3, mHealth);
    setData(4, mTankSpeed);
    setData(5, false); // is need to destroy
}

bool StaticBlock::isDestructible() const
{
    return mDestructible;
}

bool StaticBlock::isPerforating() const
{
    return mPerforating;
}

int StaticBlock::tankSpeed() const
{
    return mTankSpeed;
}

int StaticBlock::health() const
{
    return mHealth;
}

void StaticBlock::advance(int phase)
{
    if (phase && data(5).toBool()) {
        delete this;
    }
}
