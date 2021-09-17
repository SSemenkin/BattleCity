#ifndef GRAPHICSPIXMAPOBJECT_H
#define GRAPHICSPIXMAPOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "bullet.h"
#include <QDebug>

class GraphicsPixmapObject : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit GraphicsPixmapObject(const QPixmap& pixmap = QPixmap(), QGraphicsItem *graphicsParent = nullptr, QObject *parent = nullptr);

    enum class Direction : int8_t {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };

signals:

protected:
    void advance(int phase) override;
    ///
    /// \brief canDoNextStep return can you item move to position (point)
    /// \param point
    /// \return
    ///
    virtual bool canDoNextStep(const QPointF &point) const;
    bool canDoNextStep(int x, int y) const;
    void moveByIfNotWall(int x, int y);
    void fire();


    Direction mDirection {Direction::UP};
    bool mCanFire {true};
    bool isStarBonus {false};

    int CURRENT_SPEED {0};
    int PLAYER_MAX_SPEED {3};
    int BULLET_SPEED {5};

    GraphicsPixmapObject::Direction newDirection(Qt::Key key);
    void rotatePixmap(qreal angle);

};

#endif // GRAPHICSPIXMAPOBJECT_H
