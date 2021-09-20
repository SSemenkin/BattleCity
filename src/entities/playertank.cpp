#include "playertank.h"

PlayerTank::PlayerTank(int width) :
    Tank(QPixmap(":/images/tank.png").scaled(width, width))
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    setLivesLeft(3);
    createShield();
}

void PlayerTank::pickupBonus(int type)
{
    Bonus::Type bonusType = static_cast<Bonus::Type>(type);

    switch(bonusType) {
        case Bonus::Type::Granade:
        case Bonus::Type::Shovel:
            emit picked(static_cast<int>(bonusType));
            break;
        case Bonus::Type::Shield:
            createShield();
            break;
        case Bonus::Type::Star:
            break;
    }
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

bool PlayerTank::canMoveInDirection(int dx, int dy) const
{
    QPointF m_pos = scenePos();
    m_pos.setX(m_pos.x() + dx);
    m_pos.setY(m_pos.y() + dy);

    Entity* entity = qgraphicsitem_cast<Entity*>(scene()->itemAt(m_pos, sceneTransform()));
    if (entity && entity->entityName() == "Bonus") {
        entity->setPicked(true);
    }
    return Tank::canMoveInDirection(dx, dy);
}

void PlayerTank::createShield()
{
    if (m_shield) {
        m_shield->resetTimer();
    } else {
        m_shield = new Shield(this, pixmap().width());
        QObject::connect(m_shield, &Entity::destroyed, this, [this](){
            m_shield = nullptr;
        });
    }
}

void PlayerTank::takeDamage()
{
    if (m_shield) {
        return;
    } else Entity::takeDamage();
}

