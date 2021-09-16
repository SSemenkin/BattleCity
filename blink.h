#ifndef BLINK_H
#define BLINK_H

#include <QTimer>


#include "enemytank.h"

class Blink : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Blink(int widthBlock, QObject *parent = nullptr);
    void startAnimation();

signals:
    void enemyCreated(EnemyTank *enemy);

private:
    QTimer *mTimer;
    int mFrame {0};
    int mBlockWidth;
private:
    void spawnEnemy();
};

#endif // BLINK_H
