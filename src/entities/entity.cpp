#include "entity.h"

Entity::Entity(const QPixmap &pixmap, QGraphicsItem *parentItem, QObject *parent):
    QObject(parent), QGraphicsPixmapItem(pixmap, parentItem)
{
    setRequireToDestroy(false);
}

void Entity::setProperty(const Entity::Property &key, const QVariant &value) &
{
    m_properties.insert(key, value);
}

const QVariant& Entity::getProperty(const Entity::Property &key) const &
{
    return *m_properties.find(key);
}

bool Entity::isDestructible() const
{
    return getProperty(Entity::Property::Destructible).toBool();
}

void Entity::setDestructible(bool state)
{
    setProperty(Entity::Property::Destructible, state);
}

bool Entity::isBulletCanMoveThroughObject() const
{
    return getProperty(Entity::Property::CanBulletMovesThroughObject).toBool();
}

void Entity::setBulletCanMoveThroughObject(bool state)
{
    setProperty(Entity::Property::CanBulletMovesThroughObject, state);
}

bool Entity::isActorCanMoveThroughObject() const
{
    return getProperty(Entity::Property::CanActorMovesThroughObject).toBool();
}

void Entity::setActorCanMoveThroughObject(bool state)
{
    setProperty(Entity::Property::CanActorMovesThroughObject, state);
}

uint Entity::livesLeft() const
{
    return getProperty(Entity::Property::LivesLeft).toUInt();
}

void Entity::setLivesLeft(uint livesLeft)
{
    setProperty(Entity::Property::LivesLeft, livesLeft);
    if (livesLeft == 0) {
        setRequireToDestroy();
    }
}

bool Entity::isRequireToDestroy() const
{
    return getProperty(Entity::Property::RequireToDestroy).toBool();
}

void Entity::setRequireToDestroy(bool state)
{
    setProperty(Entity::Property::RequireToDestroy, state);
}

QString Entity::entityName() const
{
    return getProperty(Entity::Property::EntityName).toString();
}

void Entity::setEntityName(const QString &name)
{
    setProperty(Entity::Property::EntityName, name);
}

void Entity::takeDamage()
{
    int lives = livesLeft();
    lives--;
    setLivesLeft(lives);
}

void Entity::advance(int phase)
{
    if (phase) {
        if (isRequireToDestroy()) {
            delete this;
        }
    }
}

