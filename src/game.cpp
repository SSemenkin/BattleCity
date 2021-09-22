#include "game.h"

QVector<Level> Game::m_levelVector = {
    Level(":/levels/1_level.txt"),
    Level(":/levels/2_level.txt"),
    Level(":/levels/3_level.txt")
};

Game *Game::init()
{
    static Game game;
    return &game;
}

Game::Game() :
    m_view(new QGraphicsView),
    m_menuScene(new MenuScene)
{
    m_menuScene->initLevels(m_levelVector);

    toMenu();

    QObject::connect(m_menuScene.data(), &MenuScene::startGameAtLevel, this, &Game::startGameAtLevel);
    QObject::connect(m_menuScene.data(), &MenuScene::quit, m_view.data(), &QGraphicsView::close);

    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->showFullScreen();
}

void Game::startGameAtLevel(int levelId)
{
    m_gameScene.reset(new GameScene);
    m_gameScene->loadLevel(m_levelVector.at(levelId));

    m_view->setScene(m_gameScene.data());
    QObject::connect(m_gameScene.data(), &GameScene::toMenu, this, &Game::toMenu);
}

void Game::toMenu()
{
    m_view->setScene(m_menuScene.data());
}

