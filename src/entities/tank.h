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

    void shoot();
protected:
    bool m_fire {true};
    static int TANK_SPEED;
    int m_speed {0};
protected:
    bool canMoveInDirection(int dx, int dy) const;
    void moveAndCollide(int dx, int dy);
    void advance(int phase) override;


};

#endif // TANK_H
