#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Score : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Score(QObject *parent = nullptr);
    void startAnimation();

signals:

private:
    QTimer *mTimer;
    int mCall{0};
};

#endif // SCORE_H
