#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>

#include "entities/entity.h"
#include "scenes/menuscene.h"
#include "scenes/gamescene.h"


class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    Game(const Game& rhs) = delete;
    Game& operator=(const Game& rhs) = delete;

    void start();

private:
    /// now member on right order definition
    /// if QGraphicsView will deleted before them scenes you will have trouble ( uses nullptr in QGraphicsScene::~QGraphicsScene())

    QScopedPointer<GameScene> m_gameScene;
    QScopedPointer<MenuScene> m_menuScene;
    QScopedPointer<QGraphicsView> m_view;

    static QVector<Level> m_levelVector;

private:
    void startGameAtLevel(int levelId);
    void toMenu();
};

#endif // GAME_H
