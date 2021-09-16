#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QTimer>


#include "multimedia.h"

#include "menuScene.h"
#include "gamescene.h"
#include "player.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    ~Game();
    bool init();
private:
    MenuScene *menuScene;
    Multimedia *multimedia;
    QGraphicsView *view;
private:
    void startGameAtLevel(int level);
    void swapScenes();
};

#endif // GAME_H
