#include "tank.h"

Tank::Tank(const QPixmap &pixmap, QGraphicsItem *item, QObject *parent) :
    RigidBody(pixmap, item, parent)
{
    setDestructible(true);
    setBulletCanMoveThroughObject(false);
    setActorCanMoveThroughObject(false);
}

bool Tank::canMoveInDirection(int dx, int dy) const
{
    QPointF m_pos = scenePos();
    m_pos.setX(m_pos.x() + dx);
    m_pos.setY(m_pos.y() + dy);

    QGraphicsItem *itemAtPoint = scene()->itemAt(m_pos, sceneTransform());

    Entity* entity = qgraphicsitem_cast<Entity*>(itemAtPoint);
    if (entity) {
        return entity->isActorCanMoveThroughObject();
    } else if (!itemAtPoint && m_pos.x() > 0 && m_pos.y() > 0
               && m_pos.x() < borderPoint().x() && m_pos.y() < borderPoint().y()) {
        return true;
    } else return false;
}

void Tank::moveAndCollide(int dx, int dy)
{
    switch (m_direction) {
        case Direction::Up:
        {
            bool r = canMoveInDirection(dx, dy) && canMoveInDirection(pixmap().width()/2 + dx, dy) &&
                    canMoveInDirection(pixmap().width() + dx, dy);
            if (r) {
                moveBy(dx, dy);
            }
            break;
        }
        case Direction::Down:
        {
            bool r = canMoveInDirection(dx, dy + pixmap().height()) && canMoveInDirection(pixmap().width()/2 + dx, dy + pixmap().height()) &&
                    canMoveInDirection(pixmap().width() + dx, dy + pixmap().height());
            if (r) {
                moveBy(dx, dy);
            }
            break;
        }
        case Direction::Right:
        {
            bool r = canMoveInDirection(dx + pixmap().width(), dy) && canMoveInDirection(dx + pixmap().width(), dy + pixmap().height()/2) &&
                    canMoveInDirection(dx + pixmap().height(), dy + pixmap().height());
            if (r) {
                moveBy(dx, dy);
            }
            break;
        }
        case Direction::Left:
        {
            bool r = canMoveInDirection(dx, dy) && canMoveInDirection(dx, dy + pixmap().height()/2) &&
                    canMoveInDirection(dx, dy + pixmap().height());
            if (r) {
                moveBy(dx, dy);
            }
            break;
        }
    }
}

void Tank::advance(int phase)
{
    if (phase) {
        if (m_speed) {
            switch (m_direction) {
                case Direction::Up:
                    moveAndCollide(0, -m_speed);
                    break;
                case Direction::Down:
                    moveAndCollide(0, m_speed);
                    break;
                case Direction::Left:
                    moveAndCollide(-m_speed, 0);
                    break;
                case Direction::Right:
                    moveAndCollide(m_speed, 0);
                    break;
            }
        }
        RigidBody::advance(phase);
    }
}

void Tank::shoot()
{
    if (!m_fire) {
        return;
    }

    m_fire = false;

    Bullet *bullet = new Bullet(m_direction, pixmap().width() / 5);
    bullet->setBorderPoint(this->borderPoint());
    scene()->addItem(bullet);
    QPointF pos;
    switch(m_direction) {
        case Direction::Up:
        {
            pos.setX(x() + pixmap().width() / 2 - bullet->pixmap().width() / 2);
            pos.setY(y() - bullet->pixmap().height());
            break;
        }
        case Direction::Down:
        {
            pos.setX(x() + pixmap().width() / 2 - bullet->pixmap().width() / 2);
            pos.setY(y() + pixmap().height() + bullet->pixmap().width());
            break;
        }
        case Direction::Left:
        {
            pos.setX(x() - bullet->pixmap().width());
            pos.setY(y() + pixmap().height() / 2 - bullet->pixmap().width() / 2);
            break;
        }
        case Direction::Right:
        {
            pos.setX(x() + pixmap().width() + bullet->pixmap().width());
            pos.setY(y() + pixmap().height() / 2 - bullet->pixmap().width() / 2);
            break;
        }
    }
    bullet->setPos(pos);

    QObject::connect(bullet, &Bullet::destroyed, this, [this](){ m_fire = true; });
}
