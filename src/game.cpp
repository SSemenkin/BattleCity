#include "game.h"

Game *Game::init()
{
    static Game game;
    return &game;
}

Game::Game()
{
    m_view = new QGraphicsView();

    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->show();
}

Game::~Game() noexcept
{
    delete m_view;
}
