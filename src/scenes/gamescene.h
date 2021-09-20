#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QApplication>
#include <QScreen>

#include "entities/staticbody.h"
#include "entities/playertank.h"
#include "entities/enemytank.h"
#include "level.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

    bool loadLevel(const Level &level);
    [[nodiscard]] int levelId() const;

    [[nodiscard]] QRectF gameplayRect() const;
    [[nodiscard]] QRectF interfaceRect() const;

signals:
    void toMenu();

protected:
    QTimer *m_gameTimer;
    QTimer *m_bonusTimer;
    QTimer *m_enemySpawnTimer;

    int m_levelId;

    QRectF m_gameplayRect;
    QRectF m_interfaceRect;

    int m_lengthBlock;

    PlayerTank *m_player;

    int FPS;
    int FPS_DELTA;
    int ENEMY_RESPAWN_DELTA;
    int BONUS_RESPAWN_DELTA;
private:
    void gameOver();
    void calcRects();
    void calcContants();
    void initPlayer(const QPointF &pos);
    void spawnEnemy();
    [[nodiscard]] QPointF getAvaliablePoint() const;
    bool isCellAvaliable(const QPointF &point) const;
};

#endif // GAMESCENE_H
