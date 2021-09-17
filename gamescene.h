#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QScreen>
#include <QApplication>
#include <QTimer>
#include <vector>

#include <QGraphicsPixmapItem>

#include "level.h"
#include "player.h"
#include "base.h"
#include "gameover.h"
#include "staticblock.h"
#include "bonusitem.h"
#include "blink.h"

#include "interface.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(int level, QObject *parent = nullptr);
    explicit GameScene(QObject *parent = nullptr);
    void loadLevel(int level);
    static std::vector<Level> avaliableLevels();

signals:
    ///
    /// \brief emits when game over(Base is destroyed) or player is killed all enemies
    ///
    void swapScenes();

private:
    static std::vector<Level> levels;
    static int FPS;
    static int FPS_REFRESH_DELTA;
    static int BONUS_RESPAWN_DELTA;
    static int ENEMY_RESPAWN_DELTA;
    static int ENEMY_MAX_COUNTER;

    QTimer mGameTimer;
    QTimer mBonusItemTimer;
    QTimer mEnemyRespawnTimer;

    int mHeightBrick;
    int mWidthBrick;
    int mWidthBrickCount;
    int mHeightBrickCount;
    int mCurrentLevel{-1};
    int mEnemiesSpawned {0};
    int mDestroyed {0};

    Base *mBase;
    Player *mPlayer;
    Interface *mInterface;

private:
    void initPlayer(const QPair<int,int> &position);
    void initBase(const QPair<int, int> &position);
    void initInterface();

    void spawnBlink();
    void spawnBonus();

    void gameOver();

    QPair<int, int> getRandomAndAvaliableCell() const;
    bool isCellAvaliable(int width, int height) const;

    void createBorderAroundBase();
    void removeItemAndCreateSteel(int x, int y);

    void destroyAllEnemies();
    void createExplosionAt(const QPointF &point);

};

#endif // GAMESCENE_H
