#include "bullet.h"
#include <QPen>

Bullet::Bullet(int dx, int dy, QObject *parent) :
    QObject(parent),
    QGraphicsPixmapItem(QPixmap(":/images/bullet.png")),
    m_dx(dx),
    m_dy(dy)
{
    if (dx == 0  && dy > 0) {
        rotatePixmap(180);
    } else if (dx > 0 && dy == 0) {
        rotatePixmap(90);
    } else if (dx < 0 && dy == 0) {
        rotatePixmap(-90);
    }
}

void Bullet::advance(int phase)
{
    if (deleteOnNextIteration) {
        emit destroyed();
        delete this;
        return;
    }
    if (phase) {
        moveBy(m_dx, m_dy);
    }
    if (scenePos().x() > scene()->width() + 1 ||
          scenePos().x() < scene()->sceneRect().x() ||
          scenePos().y() < scene()->sceneRect().y() ||
          scenePos().y() > scene()->height() + 1) {
        emit destroyed();
        delete this;
        return;
    } if (!collidingItems().isEmpty()) {
        Explosion *e = new Explosion;
        scene()->addItem(e);
        e->setPos(centerOfItem(qgraphicsitem_cast<QGraphicsPixmapItem*>(collidingItems().first())));
        e->startAnimation();

        delete collidingItems().first();

        deleteOnNextIteration = true;
    }
}

void Bullet::rotatePixmap(qreal angle)
{
    QPixmap m = pixmap();
    QTransform t;
    t.rotate(angle);
    setPixmap(m.transformed(t));
}

QPointF Bullet::centerOfItem(QGraphicsPixmapItem *item)
{
    QPointF r = item->scenePos();
    r.setX(r.x());
    r.setY(r.y());
    return r;
}
