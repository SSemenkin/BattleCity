#include <QApplication>
#include "gameview.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    GameView gameView;
    gameView.showFullScreen();

    return application.exec();
}
