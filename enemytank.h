#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QObject>
#include <QGraphicsPixmapItem>

class EnemyTank : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EnemyTank(QObject *parent = nullptr);
signals:

};

#endif // ENEMYTANK_H
