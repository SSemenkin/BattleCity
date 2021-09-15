#include "game.h"


bool Game::init()
{
    static MenuScene initScene;
    static Multimedia mPlayer;
    //mPlayer.playMainTheme();
    initScene.init();
    static QTimer timer;
    static QGraphicsView view(&initScene);

    QObject::connect (&initScene, &MenuScene::playTrigerred, [] () {
        GameScene *gameScene = new GameScene;
        gameScene->loadLevel(0);
        view.setScene(gameScene);

        QObject::connect(&timer, &QTimer::timeout, view.scene(), &QGraphicsScene::advance);
    });
    QObject::connect(&timer, &QTimer::timeout, view.scene(), &QGraphicsScene::advance);
    timer.start(1000/60);


    view.setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);


    view.showFullScreen();
    return true;
}
