#ifndef BLINK_H
#define BLINK_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "enemytank.h"

class Blink : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Blink(int widthBlock, QObject *parent = nullptr);
    void startAnimation();

signals:

private:
    QTimer *mTimer;
    int mFrame {0};
    int mWidhtBlock;
private:
    void spawnEnemy();
};

#endif // BLINK_H
