#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QGraphicsPixmapItem>

class GameOver : public QGraphicsPixmapItem
{
public:
    GameOver(const QPointF &finishPos,
             const QPixmap &pixmap = QPixmap(":/images/gameover.png"), QGraphicsItem* parent = nullptr);

protected:
    void advance(int phase) override;
private:
    QPointF mFinish;
};

#endif // GAMEOVER_H
