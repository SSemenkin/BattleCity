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

Game::Game()
{
    m_view = new QGraphicsView;
    m_menuScene = new MenuScene;

    startGameAtLevel(0);

    QObject::connect(m_menuScene, &MenuScene::startGameAtLevel, this, &Game::startGameAtLevel);

    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->showFullScreen();
}

void Game::startGameAtLevel(int levelId)
{
    if (m_gameScene) {
        delete m_gameScene;
    }
    m_gameScene = new GameScene;
    m_gameScene->loadLevel(m_levelVector.at(levelId));

    m_view->setScene(m_gameScene);
    QObject::connect(m_gameScene, &GameScene::toMenu, this, &Game::toMenu);
}

void Game::toMenu()
{
    m_view->setScene(m_menuScene);
}

Game::~Game() noexcept
{
    m_menuScene->deleteLater();
    if (m_gameScene)
        m_gameScene->deleteLater();
    m_view->deleteLater();
}
