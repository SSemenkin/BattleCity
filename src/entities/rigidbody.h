#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "entities/entity.h"

class RigidBody : public Entity
{
    Q_OBJECT
public:
    explicit RigidBody(const QPixmap &pixmap = QPixmap(),
                       QGraphicsItem *graphicsParent = nullptr,
                       QObject *parent = nullptr);

protected:
    enum class Direction : int8_t {
        Up = 0,
        Down,
        Left,
        Right
    };
    enum class ObjectType : int8_t {
        NonType,
        Bullet,
        Actor
    };

    Direction m_direction {Direction::Up};
    ObjectType m_objectType {ObjectType::NonType};

protected:
    void rotatePixmap(qreal angle);
    void rotatePixmap(Direction currDir, Direction newDir);
    Direction getNewDirection(Qt::Key key);

};

#endif // RIGIDBODY_H
