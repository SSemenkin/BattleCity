#include "game.h"


bool Game::init()
{
    static MenuScene initScene;
    static Multimedia mPlayer;
    //mPlayer.playMainTheme();
    initScene.init();
    static QTimer timer;
    static QGraphicsView view(&initScene);

    QObject::connect (&initScene, &MenuScene::playTrigerred, [] () {
        view.setScene(new GameScene);
        view.scene()->setStickyFocus(true);
        Player *player = new Player(QPixmap(":/images/tank.png").scaled(64, 64));
        view.scene()->addItem(player);
        player->setPos(view.scene()->width()/2 - player->pixmap().width()/2,
                       view.scene()->height() - player->pixmap().height() - 64 - 64);
        QObject::connect(&timer, &QTimer::timeout, view.scene(), &QGraphicsScene::advance);
    });
    QObject::connect(&timer, &QTimer::timeout, view.scene(), &QGraphicsScene::advance);
    timer.start(1000/60);


    view.setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);


    view.showFullScreen();
    return true;
}
