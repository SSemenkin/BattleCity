#include "player.h"

int Player::CURRENT_SPEED = 0;
int Player::PLAYER_SPEED = 3;
int Player::BULLET_SPEED = 5;

Player::Player(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
    setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsFocusable);
    setFocus();
    setData(0, "Player");
}

void Player::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        mDirection = newDirection(static_cast<Qt::Key>(e->key()));
        CURRENT_SPEED = PLAYER_SPEED;
        break;
    case Qt::Key_Space:
        fire();
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(e);
    }
}

void Player::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        CURRENT_SPEED = 0;
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(e);
    }
}

void Player::advance(int phase)
{
    if (!phase) return;
    switch(mDirection) {
    case Direction::DOWN:
        moveByIfNotWall(0, CURRENT_SPEED);
        break;
    case Direction::UP:
        moveByIfNotWall(0, -CURRENT_SPEED);
        break;
    case Direction::LEFT:
        moveByIfNotWall(-CURRENT_SPEED, 0);
        break;
    case Direction::RIGHT:
        moveByIfNotWall(CURRENT_SPEED, 0);
        break;
    }

}

bool Player::canDoNextStep(const QPointF &point) const
{
    QPointF leftTopPoint = scenePos();
    leftTopPoint.setX(leftTopPoint.x() + point.x());
    leftTopPoint.setY(leftTopPoint.y() + point.y());

    QGraphicsItem *l = scene()->itemAt(leftTopPoint, sceneTransform());

    return !l && l != this /*&& !r && r != this*/;
}

bool Player::canDoNextStep(int x, int y) const
{
    return canDoNextStep(QPointF(x,y));
}

void Player::moveByIfNotWall(int x, int y)
{
    if(mDirection == Direction::DOWN) {
        if (canDoNextStep(x, y + pixmap().height() ) && canDoNextStep(x + pixmap().width(), y + pixmap().height()) &&
                canDoNextStep(x + pixmap().width()/2, y + pixmap().height())) {
            moveBy(x, y);
        }
    } else if (mDirection == Direction::RIGHT) {
        if (canDoNextStep(x + pixmap().width(), y) && canDoNextStep(x + pixmap().width(), y + pixmap().height()) &&
                canDoNextStep(x + pixmap().width(), y + pixmap().height()/2)) {
            moveBy(x, y);
        }
    } else if (mDirection == Direction::UP) {
        if (canDoNextStep(x, y) && canDoNextStep(x + pixmap().width(), y) && canDoNextStep(x + pixmap().width()/2, y)) {
            moveBy(x, y);
        }
    } else {
        if (canDoNextStep(x, y) && canDoNextStep(x, y + pixmap().height()) && canDoNextStep(x, y + pixmap().height()/2)) {
            moveBy(x, y);
        }
    }
}

Player::Direction Player::newDirection(Qt::Key key)
{
    if(mDirection == Direction::UP && key == Qt::Key_Left) {
        rotatePixmap(-90);
        return Direction::LEFT;
    } else if (mDirection == Direction::UP && key == Qt::Key_Right) {
        rotatePixmap(90);
        return Direction::RIGHT;
    } else if (mDirection == Direction::UP && key == Qt::Key_Down) {
        rotatePixmap(180);
        return Direction::DOWN;
    } else if (mDirection == Direction::LEFT && key == Qt::Key_Down) {
        rotatePixmap(-90);
        return Direction::DOWN;
    } else if (mDirection == Direction::LEFT && key == Qt::Key_Up) {
        rotatePixmap(90);
        return Direction::UP;
    } else if (mDirection == Direction::LEFT && key == Qt::Key_Right) {
        rotatePixmap(180);
        return Direction::RIGHT;
    } else if (mDirection == Direction::RIGHT && key == Qt::Key_Left) {
        rotatePixmap(-180);
        return Direction::LEFT;
    } else if (mDirection == Direction::RIGHT && key == Qt::Key_Up) {
        rotatePixmap(-90);
        return Direction::UP;
    } else if (mDirection == Direction::RIGHT && key == Qt::Key_Down) {
        rotatePixmap(90);
        return Direction::DOWN;
    } else if (mDirection == Direction::DOWN && key == Qt::Key_Left) {
        rotatePixmap(90);
        return Direction::LEFT;
    } else if (mDirection == Direction::DOWN && key == Qt::Key_Up) {
        rotatePixmap(180);
        return Direction::UP;
    } else if (mDirection == Direction::DOWN && key == Qt::Key_Right){
        rotatePixmap(-90);
        return Direction::RIGHT;
    }
    return mDirection;
}

void Player::rotatePixmap(qreal angle)
{
    QPixmap p = pixmap();

    QTransform t;
    t.rotate(angle);

    setPixmap(p.transformed(t));
}

void Player::fire()
{
    if (!canFire) {
        return;
    }
    canFire = false;
    Bullet *newBullet;
    QPoint bulletPosition;
    switch (mDirection) {
    case Direction::UP:
        newBullet = new Bullet(0, -BULLET_SPEED);
        bulletPosition.setX(scenePos().x() + pixmap().width()/2 - newBullet->pixmap().width()/2);
        bulletPosition.setY(scenePos().y() - 15);
        break;
    case Direction::DOWN:
        newBullet = new Bullet(0, BULLET_SPEED);
        bulletPosition.setX(scenePos().x() + pixmap().width()/2 - newBullet->pixmap().width()/2);
        bulletPosition.setY(scenePos().y() + pixmap().height() + 1);
        break;
    case Direction::LEFT:
        newBullet = new Bullet(-BULLET_SPEED, 0);
        bulletPosition.setX(scenePos().x() - 15);
        bulletPosition.setY(scenePos().y() + pixmap().height()/2 - newBullet->pixmap().height()/2);
        break;
    case Direction::RIGHT:
        newBullet = new Bullet(BULLET_SPEED, 0);
        bulletPosition.setX(scenePos().x() + pixmap().width() + 1);
        bulletPosition.setY(scenePos().y() + pixmap().height()/2 - newBullet->pixmap().width()/2);
        break;
    }
    scene()->addItem(newBullet);
    newBullet->setPos(bulletPosition);
    QObject::connect(newBullet, &Bullet::destroyed, this, [this] () { canFire = true; });
}
