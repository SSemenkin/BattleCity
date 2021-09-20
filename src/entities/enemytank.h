#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QTimer>

#include "entities/tank.h"

class EnemyTank : public Tank
{
public:
    explicit EnemyTank(int pixmapWidth);

private:
    QTimer *m_directionTimer;
    QTimer *m_shootTimer;
private:
    void changeDirection();
};

#endif // ENEMYTANK_H
