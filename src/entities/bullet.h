#ifndef BULLET_H
#define BULLET_H

#include "entities/rigidbody.h"
#include <QGraphicsScene>

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
    static int BULLET_SPEED;
private:
    void init();
    void handleCollision(Entity *entity);
    void handleBorderOfScene();

    //GameScene *m_gameScene {nullptr};
};

#endif // BULLET_H
