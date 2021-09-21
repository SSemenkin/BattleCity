#include "gameoveritem.h"

GameOverItem::GameOverItem(const QPointF &centerOfSceen) :
    Entity(QPixmap(":/images/gameover.png")),
    m_center(centerOfSceen)
{

}

void GameOverItem::advance(int phase)
{
    if (phase) {
        if (y() > m_center.y()) {
            moveBy(0, -2);
        } else {
            emit movedToCenter();
            setRequireToDestroy();
        }
        Entity::advance(phase);
    }
}
