#ifndef BONUSITEM_H
#define BONUSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class BonusItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum class Type : int8_t {
        Helmet = 0,
        Granade,
        Shovel,
        Star
    };
    explicit BonusItem(Type type, int sideWidth, QGraphicsItem *parent = nullptr, QObject *objectParent = nullptr);

signals:
    void picked(Type t);
protected:
    void advance(int phase) override;
private:
    Type mType;
};

#endif // BONUSITEM_H
