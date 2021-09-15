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
    if (scenePos().x() > scene()->width() || scenePos().x() < scene()->sceneRect().x() ||
            scenePos().y() < scene()->sceneRect().y() || scenePos().y() > scene()->height() || mIsDestroy) {
        destroy(); // check if bullet is in scene or collide with object on previous iteration
        return;
    }

    if (phase) {
        moveBy(m_dx, m_dy);
    }

    auto collItems = collidingItems();

    if (!collItems.isEmpty()) {
        for (QGraphicsItem *item : collItems) {
            if (item->data(0) == "Explosion" || item->data(0) == "Bonus")  {
                continue;
            }
            item->data(0) == "StaticBody" ? handleStaticBodyCollision(item) :
                                            handleDynamicBodyCollision(item);
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

void Bullet::createExplosion(QGraphicsItem *item)
{
    Explosion *e = new Explosion;
    scene()->addItem(e);
    e->setFixedScenePos(centerOfItem(qgraphicsitem_cast<QGraphicsPixmapItem*>(item)));
    e->startAnimation();
}

void Bullet::destroy()
{
    emit destroyed();
    delete this;
}

void Bullet::handleStaticBodyCollision(QGraphicsItem *item)
{
    if (item->data(1).toBool()) return; // if Performating
    if (!item->data(2).toBool()) return; // if not destructible

    createExplosion(item);
    int itemHealth = item->data(3).toInt();
    --itemHealth;

    itemHealth <= 0 ? item->setData(5, true) : item->setData(3, itemHealth);
    mIsDestroy = true;
}

void Bullet::handleDynamicBodyCollision(QGraphicsItem *item)
{
    createExplosion(item);
    delete item;
    mIsDestroy = true;
}
