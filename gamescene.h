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
#include "staticblock.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(int level, QObject *parent = nullptr);
    explicit GameScene(QObject *parent = nullptr);
    void loadLevel(int level);

private:
    static std::array<Level, 1> levels;
    static int FPS;
    static int FPS_REFRESH_DELTA;
    static int BONUS_RESPAWN_DELTA;
    static int ENEMY_RESPAWN_DELTA;

    QTimer gameTimer;
    QTimer bonusItemTimer;
    QTimer enemyRespawnTimer;

    int heightBrick;
    int widthBrick;
    int widthBrickCount;
    int heightBrickCount;
    Base *base;
    Player *player;
    int mCurrentLevel{-1};
private:
    void initPlayer(const QPair<int, int> &playerPos);
    void initBase(const QPair<int, int> &basePos);
    void spawnEnemy();
    void spawnBonus();
    void gameOver();

    bool isCellAvaliable(int width, int height);

};

#endif // GAMESCENE_H
