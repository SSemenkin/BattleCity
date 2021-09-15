#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QPainter>
#include <QScreen>

#include <QDebug>
#include <QApplication>

#include <QGraphicsPixmapItem>
#include <QKeyEvent>

#include <QMediaPlayer>

#include "menutextitem.h"


class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MenuScene(const QRectF &sceneRect, QObject *parent = nullptr);
    explicit MenuScene(QObject *parent = nullptr);
    void init();

    virtual ~MenuScene();

signals:
    void playTrigerred();
    void quitTrigerred();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    MenuTextItem *play;
    MenuTextItem *quit;
};
#endif // MENUSCENE_H
