#include "game.h"


bool Game::init()
{
    static MenuScene initScene;
    static Multimedia mPlayer;
    //mPlayer.playMainTheme();
    initScene.init();
    static QGraphicsView view(&initScene);

    QObject::connect (&initScene, &MenuScene::playTrigerred, [] () {
        GameScene *gameScene = new GameScene;
        gameScene->loadLevel(0);
        view.setScene(gameScene);
    });
    QObject::connect(&initScene, &MenuScene::quitTrigerred, &view, &QGraphicsView::close);


    view.setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);


    view.showFullScreen();
    return true;
}
