#include "blink.h"

Blink::Blink(int widthBlock, QObject *parent) :
    QObject(parent),
    mBlockWidth(widthBlock)
{
    setPixmap(QPixmap(":/images/blink/blink1.png").scaled(mBlockWidth, mBlockWidth));

}

void Blink::startAnimation()
{
    mTimer = new QTimer(this);
    QObject::connect(mTimer, &QTimer::timeout, this, [this] () {
       mFrame++;
       switch (mFrame) {
           case 5:
           case 1:
           {
               setPixmap(QPixmap(":/images/blink/blink2.png").scaled(mBlockWidth, mBlockWidth));
               break;
           }
           case 6:
           case 2:
           {
               setPixmap(QPixmap(":/images/blink/blink3.png").scaled(mBlockWidth, mBlockWidth));
               break;
           }
           case 7:
           case 3:
           {
               setPixmap(QPixmap(":/images/blink/blink4.png").scaled(mBlockWidth, mBlockWidth));
               break;
           }
           case 8:
           {
                spawnEnemy();
                delete this;
                break;
           }
           case 4:
           {
                setPixmap(QPixmap(QPixmap(":/images/blink/blink1.png")).scaled(mBlockWidth, mBlockWidth));
                break;
           }
        }
    });

    mTimer->start(150);
}

void Blink::spawnEnemy()
{
    EnemyTank *enemyTank = new EnemyTank(mBlockWidth);
    scene()->addItem(enemyTank);
    enemyTank->setPos(scenePos());
    emit enemyCreated(enemyTank);
}
