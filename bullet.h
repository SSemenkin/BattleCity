#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "explosion.h"
#include "base.h"

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
    bool mIsDestroy {false};
private:
    void rotatePixmap(qreal angle);
    QPointF centerOfItem(QGraphicsPixmapItem *item);
    bool isExplosion(QGraphicsItem *item) const;
    bool isBase(QGraphicsItem *item) const;
    void createExplosion(QGraphicsItem *item);
    void destroy();
    void handleStaticBodyCollision(QGraphicsItem *item);
    void handleDynamicBodyCollision(QGraphicsItem *item);
};

#endif // BULLET_H
