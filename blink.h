#ifndef BLINK_H
#define BLINK_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class Blink : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Blink(QObject *parent = nullptr);

signals:

};

#endif // BLINK_H
