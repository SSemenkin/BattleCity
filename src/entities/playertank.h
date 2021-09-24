#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include <QKeyEvent>

#include "entities/tank.h"
#include "entities/bonus.h"
#include "entities/shield.h"


class PlayerTank final : public Tank
{
    Q_OBJECT
public:
    explicit PlayerTank(int width);
    void pickupBonus(int type);
    void setRespawnPos(const QPointF &respawn);
    const QPointF &respawnPos() const;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    virtual bool canMoveInDirection(int dx, int dy) const override;
private:
    void createShield();
    void respawn();
    virtual void takeDamage() override;
private:
    Shield *m_shield {nullptr};
    QPointF m_respawn;
    QVector<Qt::Key> m_directionQueue;
};

#endif // PLAYERTANK_H
