﻿#include "graphicspixmapobject.h"

GraphicsPixmapObject::GraphicsPixmapObject(const QPixmap &pixmap, QGraphicsItem *graphicsParent, QObject *parent) :
    QObject(parent),
    QGraphicsPixmapItem(pixmap, graphicsParent)
{

}

void GraphicsPixmapObject::advance(int phase)
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

bool GraphicsPixmapObject::canDoNextStep(const QPointF &point) const
{
    QPointF basePoint = scenePos();
    basePoint.setX(basePoint.x() + point.x());
    basePoint.setY(basePoint.y() + point.y());

    QGraphicsItem *l = scene()->itemAt(basePoint, sceneTransform());

    const QString objectType = l->data(0).toString();

    if (objectType == "Score" || objectType == "Bonus") {
        return true;
    }

    else {
        if (l->data(0) == "StaticBody") {
            return l->data(6).toBool();
        } else {
            return !l && l != this && basePoint.x() > 0 && basePoint.x() < scene()->width()
                    && basePoint.y() > 0 && basePoint.y() < scene()->height();
        }
    }
}

bool GraphicsPixmapObject::canDoNextStep(int x, int y) const
{
    return canDoNextStep(QPointF(x, y));
}

void GraphicsPixmapObject::moveByIfNotWall(int x, int y)
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

void GraphicsPixmapObject::fire()
{
    if (mCanFire || isStarBonus) {
        Bullet *newBullet {nullptr};
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
        if (mCanFire) {
            QObject::connect(newBullet, &Bullet::destroyed, this, [this] () { mCanFire = true; });
        }
        mCanFire = false;
    }
}

GraphicsPixmapObject::Direction GraphicsPixmapObject::newDirection(Qt::Key key)
{
    if (key == Qt::Key_A) {
        key = Qt::Key_Left;
    }
    if (key == Qt::Key_D) {
        key = Qt::Key_Right;
    }
    if (key == Qt::Key_S) {
        key = Qt::Key_Down;
    }
    if (key == Qt::Key_W) {
        key = Qt::Key_Up;
    }

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

void GraphicsPixmapObject::rotatePixmap(qreal angle)
{
    QPixmap p = pixmap();

    QTransform t;
    t.rotate(angle);

    setPixmap(p.transformed(t));
}