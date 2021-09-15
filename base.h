﻿#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Base : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Base(const QPixmap& pixmap = QPixmap(":/images/base.png"), QObject *parent = nullptr);

signals:
    void gameOver();

protected:
    void advance(int phase) override;
};

#endif // BASE_H
