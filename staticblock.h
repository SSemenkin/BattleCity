#ifndef STATICBLOCK_H
#define STATICBLOCK_H

#include <QGraphicsPixmapItem>

class StaticBlock : public QGraphicsPixmapItem
{
public:
    enum class Type : int8_t {
        Brick = 0,
        Bush = 1,
        Concrete = 2,
        Water = 3
    };
    StaticBlock(Type type, int blockSide, QGraphicsItem *parent = nullptr);

    bool isDestructible() const;
    bool isPerforating() const;
    int health() const;

protected:
    void advance(int phase) override;

private:
    bool mDestructible;
    bool mPerforating;
    int mHealth {0};
};

#endif // STATICBLOCK_H
