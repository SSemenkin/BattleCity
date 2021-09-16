#include "base.h"

Base::Base(const QPixmap &pixmap, QObject *parent) :
    QObject(parent), QGraphicsPixmapItem(pixmap)
{
    setData(0, "StaticBody");
    setData(1, false);
    setData(2, true);
    setData(3, 1);
    setData(4, false);
}

void Base::advance(int phase)
{
   if (phase) {

       if (isDelete) {
           return;
       }

       if (data(5).toBool()) {
           emit gameOver();
           setPixmap(QPixmap(":/images/loss.png").scaled(pixmap().size()));
           isDelete = true;
       }
   }
}
