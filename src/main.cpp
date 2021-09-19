#include <QApplication>
#include "game.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    Game *game = Game::instance();


    return application.exec();
}
