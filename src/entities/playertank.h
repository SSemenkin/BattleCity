#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include <QKeyEvent>

#include "entities/tank.h"


class PlayerTank final : public Tank
{
    Q_OBJECT
public:
    explicit PlayerTank(int width);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // PLAYERTANK_H
