#include "bullet.h"
#include <QPen>

Bullet::Bullet(int dx, int dy, QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent),
    m_dx(dx),
    m_dy(dy)
{
    setRect(0, 0, 5, 5);
    setPen(QPen(Qt::white));
    setBrush(Qt::white);
}

void Bullet::advance(int phase)
{
    if (phase) {
        moveBy(m_dx, m_dy);
    }
}
