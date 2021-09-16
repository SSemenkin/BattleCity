#include "score.h"

Score::Score(QObject *parent) : QObject(parent),
    QGraphicsPixmapItem(QPixmap(":/images/100point.png"))
{
    setData(0, "Score");
}

void Score::startAnimation()
{
    mTimer = new QTimer(this);
    QObject::connect(mTimer, &QTimer::timeout, this, [this] () {
       mCall++;
       moveBy(0, -1);
       if (mCall == 11) {
           mTimer->stop();
           delete this;
       }
    });
    mTimer->start(100);
}
