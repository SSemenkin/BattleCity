#ifndef BULLET_H
#define BULLET_H

#include "entities/rigidbody.h"
#include "entities/explosion.h"

class Bullet : public RigidBody
{
    Q_OBJECT
public:
    explicit Bullet(RigidBody::Direction direction, int width);
protected:
    void advance(int phase) override;
private:
    int m_dx {0};
    int m_dy {0};
private:
    void init();
    void handleCollision(Entity *entity);
    void handleBorderOfScene();
};

#endif // BULLET_H
