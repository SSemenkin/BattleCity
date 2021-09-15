#include "base.h"

Base::Base(const QPixmap &pixmap, QObject *parent) :
    QObject(parent), QGraphicsPixmapItem(pixmap)
{
    setData(0, "Base");
}

void Base::advance(int phase)
{
   if (phase) {
       if (data(1).toBool()) {
           emit gameOver();
           delete this;
       }
   }
}
