﻿#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>

#include <QDebug>

#include "bullet.h"

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(const QPixmap &pixmap = QPixmap(":/images/tank.png"), QGraphicsItem *parent = nullptr);
    enum class Direction {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void advance(int phase) override;
private:
    static int CURRENT_SPEED;
    static int PLAYER_SPEED;
    static int BULLET_SPEED;
    Direction mDirection {Direction::UP};
    bool canFire {true};
    bool released {false};
private:
    bool canDoNextStep(const QPointF &point) const;
    bool canDoNextStep(int x, int y) const;
    void moveByIfNotWall(int x, int y);
    Direction newDirection(Qt::Key key);
    void rotatePixmap(qreal angle);
    void fire();
    void updateTankSpeed(QGraphicsItem *item) const;

};

#endif // PLAYER_H
