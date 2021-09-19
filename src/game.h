#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>

#include <entities/entity.h>


class Game : public QWidget
{
    Q_OBJECT
public:
    static Game* instance();
    Game(const Game& rhs) = delete;
    Game& operator= (const Game& rhs) = delete;
    virtual ~Game() noexcept;

private:
    Game();

    QGraphicsView *m_view;
};

#endif // GAME_H
