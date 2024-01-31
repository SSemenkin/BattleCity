#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "entities/tank.h"
#include "entities/score.h"

class EnemyTank : public Tank
{
    Q_OBJECT
public:
    explicit EnemyTank(int pixmapWidth);
    ~EnemyTank() override;
protected:
    void advance(int phase) override;
private:
    QTimer *m_directionTimer;
    QTimer *m_shootTimer;
private:
    void changeDirection();

    static QSound destroy_sound;
};

#endif // ENEMYTANK_H
