#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include <QKeyEvent>

#include "entities/tank.h"
#include "entities/bonus.h"


class PlayerTank final : public Tank
{
    Q_OBJECT
public:
    explicit PlayerTank(int width);
    void pickupBonus(Bonus::Type type);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // PLAYERTANK_H
