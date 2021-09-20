#include "bullet.h"

int Bullet::BULLET_SPEED = 6;

Bullet::Bullet(RigidBody::Direction direction, int width) :
    RigidBody(QPixmap(":/images/bullet.png").scaled(width, width))
{
    rotatePixmap(m_direction, direction);
    m_direction = direction;
    init();
}

void Bullet::advance(int phase)
{
    if (phase) {
        moveBy(m_dx, m_dy);

        handleBorderOfScene();

        const auto items = collidingItems();
        for (int i = 0; i < items.size(); ++i) {
            Entity *entity = qgraphicsitem_cast<Entity*>(items.at(i));
            if (entity) {
                handleCollision(entity);
            }
        }

        Entity::advance(phase);
    }
}

void Bullet::init()
{
    switch(m_direction) {
        case Direction::Up:
        {
            m_dx = 0;
            m_dy = -BULLET_SPEED;
            break;
        }
        case Direction::Down:
        {
            m_dx = 0;
            m_dy = BULLET_SPEED;
            break;
        }
        case Direction::Left:
        {
            m_dx = -BULLET_SPEED;
            m_dy = 0;
            break;
        }
        case Direction::Right:
        {
            m_dx = BULLET_SPEED;
            m_dy = 0;
            break;
        }
    }
}

void Bullet::handleCollision(Entity *entity)
{
    if (entity->isBulletCanMoveThroughObject()) {
        return;
    }
    if (entity->isDestructible()) {
       entity->takeDamage();
    }

    //createExplostion
    setRequireToDestroy();

}

void Bullet::handleBorderOfScene()
{
//    GameScene *gameScene = dynamic_cast<GameScene*>(scene());
//    if (gameScene) {
//        if (x() < 0 || x() >= gameScene->gameplayRect().width() ||
//            y() >= gameScene->gameplayRect().height() || y() < 0) {
//            setRequireToDestroy();
//        }
//    } else {
        if (x() < 0 || x() >= scene()->width() ||
            y() >= scene()->height() || y() < 0) {
            setRequireToDestroy();
        }
//    }
}
