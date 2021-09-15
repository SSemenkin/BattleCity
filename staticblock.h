#ifndef STATICBLOCK_H
#define STATICBLOCK_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class StaticBlock : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum class Type : int8_t {
        Brick = 0,
        Bush = 1,
        Concrete = 2,
        Water
    };
    StaticBlock(Type type, int blockSide, QGraphicsItem *parent = nullptr);

    bool isDestructible() const;
    bool isPerforating() const;
    int tankSpeed() const;
    int health() const;

protected:
    void advance(int phase) override;

private:
    bool mDestructible;
    bool mPerforating;
    int mHealth {0};
    int mTankSpeed;
    bool swapWater {true};
    QTimer *mWaterTimer;
};

#endif // STATICBLOCK_H
