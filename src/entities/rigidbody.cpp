#include "rigidbody.h"

RigidBody::RigidBody(const QPixmap &pixmap, QGraphicsItem *graphicsParent, QObject *parent) :
    Entity(pixmap, graphicsParent, parent)
{

}

void RigidBody::rotatePixmap(qreal angle)
{
    QTransform transform;
    transform.rotate(angle);

    setPixmap(pixmap().transformed(transform));
}

void RigidBody::rotatePixmap(Direction currDir, Direction newDir)
{
    switch (currDir) {
        case Direction::Up:
        {
            switch (newDir) {
                case Direction::Up:
                    break;
                case Direction::Down:
                    rotatePixmap(180);
                    break;
                case Direction::Left:
                    rotatePixmap(-90);
                    break;
                case Direction::Right:
                    rotatePixmap(90);
                    break;
            }
            break;
        }
        case Direction::Down:
        {
            switch (newDir) {
                case Direction::Up:
                    rotatePixmap(180);
                    break;
                case Direction::Down:
                    break;
                case Direction::Left:
                    rotatePixmap(90);
                    break;
                case Direction::Right:
                    rotatePixmap(-90);
                    break;
            }
            break;
        }
        case Direction::Left:
        {
            switch (newDir) {
                case Direction::Up:
                    rotatePixmap(90);
                    break;
                case Direction::Down:
                    rotatePixmap(-90);
                    break;
                case Direction::Left:
                    break;
                case Direction::Right:
                    rotatePixmap(180);
                    break;
            }
            break;
        }
        case Direction::Right:
        {
            switch (newDir) {
                case Direction::Up:
                    rotatePixmap(-90);
                    break;
                case Direction::Down:
                    rotatePixmap(90);
                    break;
                case Direction::Left:
                    rotatePixmap(180);
                    break;
                case Direction::Right:
                    break;
            }
            break;
        }
    }
}

RigidBody::Direction RigidBody::getNewDirection(Qt::Key key)
{
    Direction direction;
    switch(key) {
    case Qt::Key_Up:
        direction = Direction::Up;
        break;
    case Qt::Key_Down:
        direction = Direction::Down;
        break;
    case Qt::Key_Left:
        direction = Direction::Left;
        break;
    case Qt::Key_Right:
        direction = Direction::Right;
        break;
    default: // i am hope that never be called
        direction = Direction::Up;
        break;
    }
    rotatePixmap(m_direction, direction);
    return direction;
}

