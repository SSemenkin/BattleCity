#include "game.h"



Game::Game(QObject *parent) : QObject(parent)
{

}

Game::~Game()
{
    view->deleteLater();
    menuScene->deleteLater();
    multimedia->deleteLater();
}

bool Game::init()
{
    menuScene = new MenuScene;
    multimedia = new Multimedia;
    multimedia->playMainTheme();

    view = new QGraphicsView(menuScene);

    QObject::connect(menuScene, &MenuScene::playTrigerred, this,[this] () {
        menuScene->initLevels(GameScene::avaliableLevels());
    });
    QObject::connect(menuScene, &MenuScene::startGameAtLevel, this, &Game::startGameAtLevel);
    QObject::connect(menuScene, &MenuScene::quitTrigerred, view, &QGraphicsView::close);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    view->showFullScreen();
    return true;
}

void Game::startGameAtLevel(int level)
{
    GameScene *scene = new GameScene(this);
    scene->loadLevel(level);
    view->setScene(scene);
    QObject::connect(scene, &GameScene::swapScenes, this, &Game::swapScenes);
}

void Game::swapScenes()
{
    view->setScene(menuScene);
}
