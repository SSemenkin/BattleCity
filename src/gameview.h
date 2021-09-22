#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>

#include "entities/entity.h"
#include "scenes/menuscene.h"
#include "scenes/gamescene.h"


class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView();
    GameView(const GameView& rhs) = delete;
    GameView& operator=(const GameView& rhs) = delete;

private:

    QScopedPointer<GameScene> m_gameScene;
    QScopedPointer<MenuScene> m_menuScene;

    static QVector<Level> m_levelVector;

private:
    void startGameAtLevel(int levelId);
    void toMenu();
};

#endif // GAMEVIEW_H
