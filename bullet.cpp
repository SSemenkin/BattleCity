#include "bullet.h"

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
    if (phase) {
        moveBy(m_dx, m_dy);
    } else {
        if (scenePos().x() > scene()->width() || scenePos().x() < scene()->sceneRect().x() ||
            scenePos().y() < scene()->sceneRect().y() || scenePos().y() > scene()->height()) {
            emit destroyed();
            delete this;
            return;
        } else {
            auto items = collidingItems(Qt::ItemSelectionMode::IntersectsItemBoundingRect);
            if (!items.isEmpty()) {

                 for (QGraphicsItem *item : items) {
                     Explosion *e = new Explosion;
                     scene()->addItem(e);
                     e->setFixedScenePos(centerOfItem(qgraphicsitem_cast<QGraphicsPixmapItem*>(item)));
                     e->startAnimation();
                     isBase(item) ? item->setData(1, true) : delete item;
                 }
                 emit destroyed();
                 delete this;
            }
        }
    }
}

void Bullet::rotatePixmap(qreal angle)
{
    QPixmap m = pixmap();
    QTransform t;
    t.rotate(angle);
    setPixmap(std::move(m.transformed(t)));
}

QPointF Bullet::centerOfItem(QGraphicsPixmapItem *item)
{
    QPointF r = item->scenePos();
    r.setX(r.x() + item->pixmap().width() / 2);
    r.setY(r.y() + item->pixmap().height() / 2);
    return r;
}

bool Bullet::isExplosion(QGraphicsItem *item) const
{
    return qgraphicsitem_cast<Explosion*>(item) != nullptr;
}

bool Bullet::isBase(QGraphicsItem *item) const
{
    return qgraphicsitem_cast<Base*>(item) != nullptr && item->data(0).toString() == "Base";
}
