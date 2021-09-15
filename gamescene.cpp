#include "gamescene.h"
#include <QTimer>

std::array<Level, 1> GameScene::levels = {
  Level(":/levels/1_level.txt")
};

GameScene::GameScene(int level, QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::gray);
    setSceneRect(qApp->primaryScreen()->availableGeometry());
    loadLevel(level);
}

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::gray);
    setSceneRect(qApp->primaryScreen()->availableGeometry());
}

void GameScene::loadLevel(int levelID)
{
    const Level level = levels[levelID];
    matrix<int> structure = level.getLevelStructure();

    if(structure.size()) {

        heightBrick = height() / structure.size();
        widthBrick = width() / structure.first().size();
        std::min(heightBrick, widthBrick) == heightBrick ? widthBrick = heightBrick :
                                                           heightBrick = widthBrick ;

        static QPixmap brick(":/images/brick.png");
        brick = brick.scaled(widthBrick, heightBrick);

        for (int i = 0 ; i < structure.size(); ++i) {
            for (int j = 0; j < structure.at(i).size(); ++j) {
                if(structure.at(i).at(j) == 42) {
                    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(brick);
                    addItem(item);
                    item->setPos(j * widthBrick, i * heightBrick );
                }
            }
        }
        initPlayer(level.getPlayerPosition());
        initBase(level.getBasePosition());
    }
}

void GameScene::initPlayer(const QPair<int, int> &playerPos)
{
    Player *player = new Player;
    player->setPixmap(player->pixmap().scaled(widthBrick, heightBrick));
    addItem(player);
    player->setPos(playerPos.first * widthBrick,
                   playerPos.second * heightBrick);
}

void GameScene::initBase(const QPair<int, int> &basePos)
{
    Base *base = new Base;
    base->setPixmap(base->pixmap().scaled(widthBrick, heightBrick));
    addItem(base);
    base->setPos(basePos.first * widthBrick,
                 basePos.second * heightBrick);
}

