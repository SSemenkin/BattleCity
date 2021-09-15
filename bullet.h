#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "explosion.h"
#include "player.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(int dx, int dy, QObject *parent = nullptr);
protected:
    void advance(int phase) override;
private:
    int m_dx;
    int m_dy;
private:
    void rotatePixmap(qreal angle);
    bool deleteOnNextIteration {false};
    QPointF centerOfItem(QGraphicsPixmapItem *item);
    bool isExplosion(QGraphicsItem *item) const;
};

#endif // BULLET_H
