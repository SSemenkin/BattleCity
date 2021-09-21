#include "base.h"

Base::Base(int width) :
    Entity(QPixmap(":/images/base.png").scaled(width, width))
{
    setDestructible(true);
}

void Base::advance(int phase)
{
    if (phase) {
        if (isRequireToDestroy()) {
            Entity *entity = new Entity(QPixmap(":/images/loss.png").scaled(pixmap().width(), pixmap().width()));
            scene()->addItem(entity);
            entity->setPos(scenePos());
        }

        Entity::advance(phase);
    }
}
