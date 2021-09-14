#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsEllipseItem>

class Bullet : public QGraphicsEllipseItem
{
public:
    Bullet(int dx, int dy, QGraphicsItem *parent = nullptr);

protected:
    void advance(int phase) override;
private:
    int m_dx;
    int m_dy;
};

#endif // BULLET_H
