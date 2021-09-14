#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>

#include <QDebug>

#include "bullet.h"

class Player : public QGraphicsPixmapItem
{
public:
    Player(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
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
private:
    bool canDoNextStep(const QPointF &point) const;
    bool canDoNextStep(int x, int y) const;
    void moveByIfNotWall(int x, int y);
    Direction newDirection(Qt::Key key);
    void rotatePixmap(qreal angle);
    void fire();
};

#endif // PLAYER_H
