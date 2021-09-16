#include "game.h"



Game::Game(QObject *parent) : QObject(parent)
{

}

bool Game::init()
{
    menuScene = new MenuScene;
    menuScene->init();
    multimedia = new Multimedia;
    multimedia->playMainTheme();

    view = new QGraphicsView(menuScene);
    QObject::connect (menuScene, &MenuScene::playTrigerred, this, &Game::startGameAtLevel);
    QObject::connect(menuScene, &MenuScene::quitTrigerred, view, &QGraphicsView::close);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    view->showFullScreen();
    return true;
}

void Game::startGameAtLevel(int level)
{
    GameScene *scene = new GameScene;
    scene->loadLevel(level);
    view->setScene(scene);
    QObject::connect(scene, &GameScene::swapScenes, this, [this] () {
       QGraphicsScene *s = view->scene();
       delete s;
       view->setScene(menuScene);
    });
}
