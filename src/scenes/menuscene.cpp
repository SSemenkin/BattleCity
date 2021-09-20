#include "menuscene.h"

MenuScene::MenuScene(QObject *parent) : QGraphicsScene(parent)
{

}

void MenuScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Enter:
        emit startGameAtLevel(0);
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
    }
}
