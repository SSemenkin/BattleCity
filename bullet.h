#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "explosion.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(int dx, int dy, QObject *parent = nullptr);
signals:
    void destroyed();
protected:
    void advance(int phase) override;
private:
    int m_dx;
    int m_dy;
private:
    void rotatePixmap(qreal angle);
    bool deleteOnNextIteration {false};
    QPointF centerOfItem(QGraphicsPixmapItem *item);
};

#endif // BULLET_H
