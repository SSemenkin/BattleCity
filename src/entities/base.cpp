#include "base.h"

Base::Base(int width) :
    Entity(QPixmap(":/images/base.png").scaled(width, width))
{

}

void Base::advance(int phase)
{
    if (phase) {
        if (isRequireToDestroy()) {
            scene()->addItem(new Entity(QPixmap(":/images/loss.png").scaled(pixmap().width(), pixmap().width())));
        }

        Entity::advance(phase);
    }
}
