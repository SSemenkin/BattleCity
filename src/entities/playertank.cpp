#include "playertank.h"

PlayerTank::PlayerTank(int width) :
    Tank(QPixmap(":/images/tank.png").scaled(width, width))
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    setLivesLeft(3);
}

void PlayerTank::pickupBonus(Bonus::Type type)
{

}

void PlayerTank::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        m_speed = TANK_SPEED;
        m_direction = getNewDirection(static_cast<Qt::Key>(event->key()));
        break;
    case Qt::Key_Space:
        shoot();
        break;
    default:
        Tank::keyPressEvent(event);
    }
}

void PlayerTank::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        m_speed = 0;
        break;
    default:
        Tank::keyPressEvent(event);
    }
}

