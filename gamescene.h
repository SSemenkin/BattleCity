#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QScreen>
#include <QApplication>
#include <QTimer>

#include <QGraphicsPixmapItem>

#include "level.h"
#include "player.h"
#include "base.h"
#include "gameover.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(int level, QObject *parent = nullptr);
    explicit GameScene(QObject *parent = nullptr);
    void loadLevel(int level);

private:
    static std::array<Level, 1> levels;
    QTimer gameTimer;
    int heightBrick;
    int widthBrick;
    Base *base;
    Player *player;
private:
    void initPlayer(const QPair<int, int> &playerPos);
    void initBase(const QPair<int, int> &basePos);
    void gameOver();

};

#endif // GAMESCENE_H
