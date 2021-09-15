#include "base.h"

Base::Base(const QPixmap &pixmap, QObject *parent) :
    QObject(parent), QGraphicsPixmapItem(pixmap)
{

}
