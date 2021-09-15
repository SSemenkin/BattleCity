#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QScreen>
#include <QApplication>

#include <QGraphicsPixmapItem>

#include "level.h"
#include "player.h"
#include "base.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(int level, QObject *parent = nullptr);
    explicit GameScene(QObject *parent = nullptr);
    void loadLevel(int level);

private:
    static std::array<Level, 1> levels;
    int heightBrick;
    int widthBrick;
private:
    void initPlayer(const QPair<int, int> &playerPos);
    void initBase(const QPair<int, int> &basePos);
};

#endif // GAMESCENE_H
