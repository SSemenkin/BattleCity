#ifndef PLAYER_H
#define PLAYER_H

#include "graphicspixmapobject.h"

#include <QKeyEvent>

#include "bonusitem.h"
#include "shield.h"

struct mShield : public QObject {
    Q_OBJECT
public:
    mShield () {
    }
    Shield *shield;
    operator bool (){
        return isNull;
    }
    QGraphicsItem* init(QGraphicsItem *item) {
        shield = new Shield(item);
        QObject::connect(shield, &Shield::destroyed, this, [this] () {
            isNull = true;
        });
        isNull = false;
        return shield;
    }
    void deinit() {
        isNull = true;
        delete shield;
    }
private:
    bool isNull {true};
};

class Player : public GraphicsPixmapObject
{
    Q_OBJECT
public:
    Player(const QPixmap &pixmap = QPixmap(":/images/tank.png"), QGraphicsItem *parent = nullptr);
    void pickupBonus(BonusItem::BonusType bonusType);
    void setRespawnPosition(const QPointF &respawn);
signals:
    void destroyEnemies();
    void createBorder();
    void currentHealthChanged(int currentHealth);
protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    virtual bool canDoNextStep(const QPointF &point) const override;
    virtual void advance(int phase) override;
private:
    void createShield();
    void createStarBonus();
    void destroy();
    void takeDamage();
    void respawn();
private:
    QPointF mRespawnPosition;
    mShield shield;
    static int STAR_BONUS_DURATION;
};

#endif // PLAYER_H
