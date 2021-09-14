#include "player.h"

int Player::speed = 0;

Player::Player(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
    setFlags(QGraphicsItem::GraphicsItemFlag::ItemIsFocusable | QGraphicsItem::GraphicsItemFlag::ItemIsMovable);
    setFocus();
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Up:
        speed = -5;
        break;
    case Qt::Key_Down:
        speed = 5;
        break;
    case Qt::Key_Left:
        rotatePixmap(-90);
        break;
    case Qt::Key_Right:
        rotatePixmap(90);
        break;
    case Qt::Key_Space:
        fire();
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
         speed = 0;
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}

void Player::advance(int phase)
{

    QPointF p = scenePos();

    if(phase) {
        switch (m_direction) {
        case Direction::left:
            moveByIfNoItemAtPosition(adjusted(p, -speed * 2, 0), speed, 0);
            break;
        case Direction::right:
            moveByIfNoItemAtPosition(adjusted(p, speed * 2, 0), -speed, 0);
            break;
        case Direction::up:
            moveByIfNoItemAtPosition(adjusted(p, 0, -speed * 2), 0, speed);
            break;
        case Direction::down:
            moveByIfNoItemAtPosition(adjusted(p, 0, speed * 2), 0, -speed);
            break;
        }

    }
}

void Player::fire()
{
    Bullet *b;
    QPoint point;
    switch (m_direction) {
    case Direction::up :
        b = new Bullet(0, -5);
        point.setX(this->x() + pixmap().width()/2);
        point.setY(this->y() - 5);
        break;
    case Direction::down :
        b = new Bullet(0, 5);
        point.setX(this->x() + pixmap().width()/2);
        point.setY(this->y() + pixmap().height() + 5);
        break;
    case Direction::left :
        b = new Bullet(-5, 0);
        point.setX(this->x());
        point.setY(this->y() + pixmap().width()/2);
        break;
    case Direction::right:
        b = new Bullet(5, 0);
        point.setX(this->x() + pixmap().width() + 5);
        point.setY(this->y() + pixmap().width()/2);
        break;
    }
    scene()->addItem(b);
    b->setPos(point);
}

bool Player::isItemAtPosition(const QPointF &point)
{
    return collidesWithItem(scene()->itemAt(point, QTransform()));
}

void Player::moveByIfNoItemAtPosition(const QPointF &point, int m_dx, int m_dy)
{
    if (!isItemAtPosition(point)) {
        moveBy(m_dx, m_dy);
    }
}

QPointF &Player::adjusted(QPointF &source, qreal x, qreal y)
{
    source.setX(source.x() + x);
    source.setY(source.y() + y);
    return source;
}

void Player::rotatePixmap(qreal angle)
{
    if(m_direction == Direction::up) {
        angle == 90 ? m_direction = Direction::right : m_direction = Direction::left;
    } else if (m_direction == Direction::down) {
        angle == 90 ? m_direction = Direction::left : m_direction = Direction::right;
    } else if (m_direction == Direction::left) {
        angle == 90 ? m_direction = Direction::up : m_direction = Direction::down;
    } else {
        angle == 90 ? m_direction = Direction::down : m_direction = Direction::up;
    }

    QTransform transform;
    transform.rotate(angle);
    QPixmap currentPixmap = pixmap();
    setPixmap(currentPixmap.transformed(transform));
}
