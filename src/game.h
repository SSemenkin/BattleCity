#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>

#include "entities/entity.h"
#include "scenes/menuscene.h"
#include "scenes/gamescene.h"


class Game : public QWidget
{
    Q_OBJECT
public:
    static Game* init();
    Game(const Game& rhs) = delete;
    Game& operator=(const Game& rhs) = delete;
    virtual ~Game() noexcept;

private:
    Game();
    QGraphicsView *m_view;
    MenuScene *m_menuScene;
    GameScene *m_gameScene {nullptr};
    static QVector<Level> m_levelVector;

private:
    void startGameAtLevel(int levelId);
    void toMenu();
};

#endif // GAME_H
