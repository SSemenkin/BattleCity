#include "menuScene.h"

MenuScene::MenuScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{

}

MenuScene::MenuScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    setSceneRect(qApp->primaryScreen()->availableGeometry());
    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));
    addItem(logo);
    logo->setPos(width()/2 - logo->pixmap().width()/2, 0);

    play = new MenuTextItem("PLAY");
    quit = new MenuTextItem("QUIT");
    back = new MenuTextItem("BACK");

    addItem(play);
    addItem(quit);
    addItem(back);
    back->hide();

    displayItems({play, quit});
    play->setCurrent(true);

    QObject::connect(play, &MenuTextItem::clicked, this, [this] () {
        emit playTrigerred();
    });
    QObject::connect(back, &MenuTextItem::clicked, this, [this] () {
        displayItems({play, quit});
    });
    QObject::connect(quit, &MenuTextItem::clicked, this, [this] () {
        emit quitTrigerred();
    });

}

void MenuScene::initLevels(const std::vector<Level> &levels)
{
    if (levelItems.isEmpty()) {
        for(std::vector<Level>::size_type i = 0; i < levels.size(); ++i) {
            MenuTextItem *item = new MenuTextItem(QString::number(levels[i].getLevelID()) + " LEVEL");
            levelItems.push_back(item);
            addItem(item);
            QObject::connect(item, &MenuTextItem::clicked, this, [this, i] () {
               emit startGameAtLevel(i);
            });
        }
    }

    displayItems(levelItems);
}

MenuScene::~MenuScene()
{
}

void MenuScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
        navigateBetweenButtons(static_cast<Qt::Key>(event->key()));
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        handleEnterPressed();
        break;
    default:
        QGraphicsScene::keyPressEvent(event);
        break;
    }
}

void MenuScene::displayItems(const QVector<MenuTextItem *> &items)
{
    hideItems(mCurrentDisplayed);

    int offset = 50;
    int centerWidth = width()/2;
    int initHeight = 0 + logo->pixmap().height() + offset + 100;

    for (MenuTextItem *item : items) {
        item->show();
        item->setPos(centerWidth, initHeight);
        mCurrentDisplayed.push_back(item);
        initHeight += offset;
    }

    if (items == levelItems) {
        back->show();
        back->setPos(centerWidth, initHeight);
        mCurrentDisplayed.push_back(back);
    }
}

void MenuScene::hideItems(const QVector<MenuTextItem *> &items)
{
    for (MenuTextItem *item : items) {
        item->hide();
        item->setCurrent(false);
    }


    mCurrentDisplayed.clear();
}

void MenuScene::navigateBetweenButtons(Qt::Key key)
{
    int currentIndex = -1;
    for (int i = 0; i < mCurrentDisplayed.size(); i++) {
        if (mCurrentDisplayed[i]->isCurrent()) {
            currentIndex = i;
            break;
        }
    }

    if (currentIndex != -1) {
        mCurrentDisplayed[currentIndex]->setCurrent(false);
        key == Qt::Key_Down ? currentIndex++ : currentIndex--;
        if (currentIndex == mCurrentDisplayed.size()) {
            mCurrentDisplayed[0]->setCurrent(true);
        } else if(currentIndex < 0) {
            mCurrentDisplayed[mCurrentDisplayed.size()-1]->setCurrent(true);
        } else {
            mCurrentDisplayed[currentIndex]->setCurrent(true);
        }
    } else {
        mCurrentDisplayed[0]->setCurrent(true);
    }
}

void MenuScene::handleEnterPressed()
{
    if (quit->isCurrent()) {
        emit quitTrigerred();
        return;
    }

    if (play->isCurrent()) {
        emit playTrigerred();
        return;
    }

    if (back->isCurrent()) {
        displayItems({play, quit});
        return;
    }

    for (MenuTextItem *item : levelItems) {
        if (item->isCurrent()) {
            qDebug() << item->toPlainText();
            emit startGameAtLevel(item->toPlainText().split(" ").first().toInt() - 1 );
            return;
        }
    }
}


