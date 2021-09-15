#ifndef BONUSITEM_H
#define BONUSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class BonusItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum class Type : int8_t {

    };
    explicit BonusItem(Type type, QObject *parent = nullptr);


signals:
    void picked(Type t);
};

#endif // BONUSITEM_H
