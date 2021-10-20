#include "gameview.h"


GameView::GameView() :
    m_menuScene(new MenuScene)
{
   m_levelVector = {
       Level(":/levels/1_level.txt"),
       Level(":/levels/2_level.txt"),
       Level(":/levels/3_level.txt"),
       Level(":/levels/4_level.txt")
   };
    m_menuScene->initLevels(m_levelVector);


    QObject::connect(m_menuScene.data(), &MenuScene::startGameAtLevel, this, &GameView::startGameAtLevel);
    QObject::connect(m_menuScene.data(), &MenuScene::quit, this, &QGraphicsView::close);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    toMenu();
}

void GameView::startGameAtLevel(int levelId)
{
    m_gameScene.reset(new GameScene);
    m_gameScene->loadLevel(m_levelVector.at(levelId));

    setScene(m_gameScene.data());
    QObject::connect(m_gameScene.data(), &GameScene::toMenu, this, &GameView::toMenu);
}

void GameView::toMenu()
{
   setScene(m_menuScene.data());
}



