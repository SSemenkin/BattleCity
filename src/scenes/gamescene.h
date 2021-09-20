#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <entities/entity.h>
#include <QTimer>

class GameScene : public QGraphicsScene
{
public:
    explicit GameScene(QObject *parent = nullptr);

    bool loadLevel(uint levelId);
    uint levelId() const;

    QRectF gameplayRect() const;
    QRectF interfaceRect() const;

protected:
    QTimer *m_gameTimer;
    QTimer *m_bonusTimer;
    QTimer *m_enemySpawnTimer;

    uint m_levelId;

    QRectF m_gameplayRect;
    QRectF m_interfaceRect;

private:
    void gameOver();

};

#endif // GAMESCENE_H
