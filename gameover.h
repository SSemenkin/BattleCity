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
    ///
    /// \brief emits when this item is
    ///
    void gameOver();

protected:
    void advance(int phase) override;
private:
    // center of scene
    QPointF mFinish;
};

#endif // GAMEOVER_H
