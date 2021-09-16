#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class GameOver : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameOver(const QPointF &finishPos,
             const QPixmap &pixmap = QPixmap(":/images/gameover.png"), QGraphicsItem* parent = nullptr);
signals:
    void gameOver();

protected:
    void advance(int phase) override;
private:
    QPointF mFinish;
};

#endif // GAMEOVER_H
