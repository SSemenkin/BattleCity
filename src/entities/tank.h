#ifndef TANK_H
#define TANK_H

#include "entities/bullet.h"

class Tank : public RigidBody
{
    Q_OBJECT
public:
    explicit Tank(const QPixmap& pixmap = QPixmap(),
                  QGraphicsItem *item = nullptr,
                  QObject *parent = nullptr);


protected:
    bool m_fire {true};
    static int TANK_SPEED;
    bool canMoveInDirection(int dx, int dy) const;
    void moveAndCollide(int dx, int dy);
protected:
    void shoot();
};

#endif // TANK_H
