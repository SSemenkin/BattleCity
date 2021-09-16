﻿#ifndef PLAYER_H
#define PLAYER_H

#include "graphicspixmapobject.h"

#include <QKeyEvent>

#include "bonusitem.h"
#include "shield.h"

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
    void refreshTimer();
    void currentHealthChanged(int currentHealth);
protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    virtual bool canDoNextStep(const QPointF &point) const override;
    virtual void advance(int phase) override;
private:
    void createShield();
    void destroy();
    void takeDamage();
    void respawn();
private:
    QPointF mRespawnPosition;

    Shield *mShield;

};

#endif // PLAYER_H
