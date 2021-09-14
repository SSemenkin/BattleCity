#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>

#include <QDebug>

#include "bullet.h"

class Player : public QGraphicsPixmapItem
{
    enum class Direction {
        left,
        right,
        up,
        down
    };

public:
    Player(const QPixmap& pixmap, QGraphicsItem *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void advance(int phase) override;
    virtual void fire();
    bool isItemAtPosition(const QPointF& point);
    void moveByIfNoItemAtPosition(const QPointF& point, int m_dx, int m_dy);
    QPointF& adjusted(QPointF& source, qreal x, qreal y);

private:
    void rotatePixmap(qreal angle);
    Direction m_direction {Direction::up};
    static int speed;
};

#endif // PLAYER_H
