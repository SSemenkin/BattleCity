#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include "bullet.h"
#include "score.h"

class EnemyTank : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EnemyTank(int widthBlock, QObject *parent = nullptr);
    enum class Direction : int8_t {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };


signals:
protected:
    void advance(int phase) override;
private:
    bool mCanFire {true};
    int mWidthBlock;
private:
    void fire();
    void spawnScore();
};

#endif // ENEMYTANK_H
