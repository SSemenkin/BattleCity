#include "gameover.h"

GameOver::GameOver(const QPointF &finishPos, const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent),
    mFinish(finishPos)
{

}

void GameOver::advance(int phase)
{
    if (phase  && scenePos().y() > mFinish.y()) {
       moveBy(0, -3);
    }
}
