﻿#ifndef BONUSITEM_H
#define BONUSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class BonusItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum class BonusType : int8_t {
        Helmet = 0,
        Granade,
        Shovel,
        Star
    };
    explicit BonusItem(BonusType type, int sideWidth, QGraphicsItem *parent = nullptr, QObject *objectParent = nullptr);

signals:
    void picked(BonusType t);
protected:
    void advance(int phase) override;
private:
    BonusType mType;
    QTimer *mRemainingTimer;
    QTimer *mSwapTimer;
    QPixmap mPixmap;
    int calls {0};
    bool mSwap {true};
};

#endif // BONUSITEM_H
