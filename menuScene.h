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
#include "level.h"


class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MenuScene(const QRectF &sceneRect, QObject *parent = nullptr);
    explicit MenuScene(QObject *parent = nullptr);
    void initLevels(const std::vector<Level> &levels);

    virtual ~MenuScene();

signals:
    void startGameAtLevel(int value);
    void playTrigerred();
    void quitTrigerred();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void displayItems(const QVector<MenuTextItem *> &items);
    void hideItems(const QVector<MenuTextItem*> &items);
    void navigateBetweenButtons(Qt::Key key);
    void handleEnterPressed();
private:
    QVector<MenuTextItem *> mCurrentDisplayed;
    MenuTextItem *play;
    MenuTextItem *quit;
    MenuTextItem *back;
    QVector<MenuTextItem*> levelItems;
    QGraphicsPixmapItem *logo;
};
#endif // MENUSCENE_H
