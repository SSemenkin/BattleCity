#ifndef SHIELD_H
#define SHIELD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Shield : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Shield(QGraphicsItem *player, QObject *parent = nullptr);

signals:

private:
    QTimer *mChangeTimer;
    bool swapImage {true};
    int calls {0};
};

#endif // SHIELD_H
