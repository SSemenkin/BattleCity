#ifndef GAMEOVERITEM_H
#define GAMEOVERITEM_H

#include "entity.h"

class GameOverItem : public Entity
{
    Q_OBJECT
public:
    explicit GameOverItem(const QPointF& centerOfSceen, int pixmapWidth);

protected:
    void advance(int phase) override;
private:
    QPointF m_center;
};

#endif // GAMEOVERITEM_H
