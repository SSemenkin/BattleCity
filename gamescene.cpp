#include "gamescene.h"

std::array<Level, 1> GameScene::levels = {
  Level(":/levels/1_level.txt")
};

GameScene::GameScene(int level, QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    setSceneRect(qApp->primaryScreen()->availableGeometry());
    loadLevel(level);
}

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    setSceneRect(qApp->primaryScreen()->availableGeometry());
}

void GameScene::loadLevel(int levelID)
{
    gameTimer.stop();
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

    QObject::connect(&gameTimer, &QTimer::timeout, this, &QGraphicsScene::advance);
    QObject::connect(base, &Base::gameOver, this, &GameScene::gameOver);
    gameTimer.start(1000/60);
}

void GameScene::initPlayer(const QPair<int, int> &playerPos)
{
    player = new Player;
    player->setPixmap(player->pixmap().scaled(widthBrick, heightBrick));
    addItem(player);
    player->setPos(playerPos.first * widthBrick,
                   playerPos.second * heightBrick);
}

void GameScene::initBase(const QPair<int, int> &basePos)
{
    base = new Base;
    base->setPixmap(base->pixmap().scaled(widthBrick, heightBrick));
    addItem(base);
    base->setPos(basePos.first * widthBrick,
                 basePos.second * heightBrick);
}

void GameScene::gameOver()
{
    //gameTimer.stop();

    GameOver *gameOverItem = new GameOver(QPointF(width()/2, height()/2));
    addItem(gameOverItem);
    gameOverItem->setPos((width() / widthBrick / 2) * widthBrick - widthBrick/2, height());
    delete player;
}



