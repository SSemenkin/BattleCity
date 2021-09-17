#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "graphicspixmapobject.h"

#include "score.h"

class EnemyTank : public GraphicsPixmapObject
{
    Q_OBJECT
public:
    explicit EnemyTank(int widthBlock, QObject *parent = nullptr);

    static int CHANGE_DIRECTION_DELTA;
    static int FIRE_DELTA;
signals:
protected:
    void advance(int phase) override;
private:
    void spawnScore();
    void changeDirection();
private:
    QTimer *mDirectionTimer;
    QTimer *mFireTimer;
    int mWidthBlock;

};

#endif // ENEMYTANK_H
