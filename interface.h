#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "menutextitem.h"

class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(QObject *parent = nullptr);

    void initItems(QGraphicsScene *scene, int height, int counter);
    void removeItem(int counter);
    void updateScore(int appedValue);
signals:

private:
    QGraphicsPixmapItem* itemAtIndex(int index);
private:
    QGraphicsPixmapItem *items;
    QGraphicsTextItem *mScoreItem;
    int mScore {0};
};

#endif // INTERFACE_H
