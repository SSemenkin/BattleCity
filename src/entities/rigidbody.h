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

    Direction m_direction {Direction::Up};

protected:
    void rotatePixmap(qreal angle);
    void rotatePixmap(Direction currDir, Direction newDir);
    Direction getNewDirection(Qt::Key key);

};

#endif // RIGIDBODY_H
