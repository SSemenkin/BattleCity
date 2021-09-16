#include "interface.h"

Interface::Interface(QObject *parent) : QObject(parent)
{

}

void Interface::initItems(QGraphicsScene *scene, int height, int counter)
{
    MenuTextItem *enemiesLeft = new MenuTextItem("ENEMIES LEFT");
    scene->addItem(enemiesLeft);
    enemiesLeft->setPos(50, height);

    mScoreItem = new MenuTextItem("Score : 0");
    scene->addItem(mScoreItem);
    mScoreItem->setPos(scene->width()/2, height);


    items = new QGraphicsPixmapItem[counter];

    int offset = 30;

    int initWidth = enemiesLeft->x() + enemiesLeft->textWidth() + offset + 100;
    for (int i = 0; i < counter; ++i) {
        items[i].setPixmap(QPixmap(":/images/health.png"));
        scene->addItem(items + i);
        int y = i % 2 ? height + items[i].pixmap().height()/3  : height - items[i].pixmap().height()/3 - items->pixmap().height()/3;
        items[i].setPos(initWidth + offset * i + items[i].pixmap().width() * 2, y);
    }

}

void Interface::removeItem(int counter)
{
    delete itemAtIndex(counter);
    updateScore(100);
}

void Interface::updateScore(int appedValue)
{
    mScore += appedValue;
    mScoreItem->setPlainText(QString("Score : " + QString::number(mScore)));
}

QGraphicsPixmapItem* Interface::itemAtIndex(int index)
{
    return items + index;
}
