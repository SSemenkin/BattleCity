#include "menuScene.h"

MenuScene::MenuScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{

}

MenuScene::MenuScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(qApp->primaryScreen()->availableGeometry());
}

MenuScene::~MenuScene()
{
}

void MenuScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
        if (play->isCurrent()) {
            play->setCurrent(false);
            quit->setCurrent(true);
        } else {
            quit->setCurrent(false);
            play->setCurrent(true);
        }
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if (quit->isCurrent()) {
            emit quitTrigerred();
        } else {
            emit playTrigerred();
        }
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
        break;
    }
}

void MenuScene::init()
{
    int offset = 10;

    setBackgroundBrush(Qt::black);

    QGraphicsPixmapItem *logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));
    play = new MenuTextItem("PLAY");
    quit = new MenuTextItem("QUIT");

    addItem(logo);
    addItem(play);
    addItem(quit);



    logo->setPos(this->width()/2 - logo->pixmap().width()/2, logo->pos().y());

    play->setPos(this->width()/2 - play->textWidth()/2, logo->pixmap().height() + (offset * 15) + play->textWidth());
    quit->setPos(this->width()/2 - quit->textWidth()/2, logo->pixmap().height() + (offset * 20) + quit->textWidth());

    play->setCurrent(true);
}


