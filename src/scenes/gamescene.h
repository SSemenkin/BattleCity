#ifndef GAMESCENE_H
#define GAMESCENE_H

#define FPS 60
#define FPS_DELTA (1000/FPS)
#define ENEMY_RESPAWN_DELTA 6000
#define BONUS_RESPAWN_DELTA 6000

#include <QGraphicsScene>
#include <QTimer>
#include <QApplication>
#include <QScreen>

#include "entities/staticbody.h"
#include "entities/playertank.h"
#include "entities/blink.h"
#include "entities/bonus.h"
#include "entities/base.h"
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
    QTimer *m_borderTimer;
    QTimer *m_borderBlinkTimer;


    int m_levelId;

    QRectF m_gameplayRect;
    QRectF m_interfaceRect;

    int m_lengthBlock;

    PlayerTank *m_player;
    Base *m_base;

    QVector<Entity *> m_hides;
    QVector<Entity *> m_border;
private:
    void gameOver();
    void calcRects();
    void spawnEnemy();
    void spawnBonus();
    void spawnBorder();
    void destroyAllEnemies();
    void removeBorder();
    void startBorderBlinking();
    void borderBlink();
    void resetBorderTimers();

    void hideEntityAndCreateConcrete(const QPointF &nearPos);
    void playerPickedBonus(int bonus);
    void initPlayer(const QPointF &pos);
    void initBase(const QPointF &pos);
    [[nodiscard]] QPointF getAvaliablePoint() const;
    [[nodiscard]] bool isCellAvaliable(const QPointF &point) const;
};

#endif // GAMESCENE_H
