#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsObject>
#include <QMap>

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Entity(const QPixmap &pixmap = QPixmap(), QGraphicsItem *parentItem = nullptr, QObject *parent = nullptr);
    virtual ~Entity() noexcept {}
    enum class Property : int8_t {
        Movable,
        Destructible,
        CanBulletMovesThroughObject,
        CanActorMovesThroughObject,
        LivesLeft,
        RequireToDestroy
    };

    bool isMovable() const;
    void setMovable(bool state);

    bool isDestructible() const;
    void setDestructible(bool state);

    bool isBulletCanMoveThroughObject() const;
    void setBulletCanMoveThroughObject(bool state);

    bool isActorCanMoveThroughObject() const;
    void setActorCanMoveThroughObject(bool state);

    uint livesLeft() const;
    void setLivesLeft(uint livesLeft);

    bool isRequireToDestroy() const;
    void setRequireToDestroy(bool state = true);

protected:
    virtual void advance(int phase) override;

    void setProperty(const Property &key, const QVariant &value) &;
    const QVariant& getProperty(const Property &key) const &;
private:
    QMap<Property, QVariant> m_properties;
};

#endif // ENTITY_H
