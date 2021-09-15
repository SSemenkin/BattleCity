#include "gamescene.h"

int GameScene::FPS = 60;
int GameScene::FPS_REFRESH_DELTA = 1000/FPS;
int GameScene::ENEMY_RESPAWN_DELTA = 1000;
int GameScene::BONUS_RESPAWN_DELTA = 10000;

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
    if(level.isOk()) {
        mCurrentLevel = levelID;
    }
    matrix<int> structure = level.getLevelStructure();

    if(structure.size()) {
        heightBrickCount = structure.size();
        widthBrickCount = structure.first().size();

        heightBrick = height() / structure.size();
        widthBrick = width() / structure.first().size();
        std::min(heightBrick, widthBrick) == heightBrick ? widthBrick = heightBrick :
                                                           heightBrick = widthBrick ;


        for (int i = 0 ; i < structure.size(); ++i) {
            for (int j = 0; j < structure.at(i).size(); ++j) {
                if (structure.at(i).at(j) != 32) {
                    StaticBlock *item = new StaticBlock(static_cast<StaticBlock::Type>(structure.at(i).at(j) - '0'), widthBrick);
                    addItem(item);
                    item->setPos(j * widthBrick, i * heightBrick);

                }
            }
        }
        initPlayer(level.getPlayerPosition());
        initBase(level.getBasePosition());
    }

    QObject::connect(&gameTimer, &QTimer::timeout, this, &QGraphicsScene::advance);
    QObject::connect(base, &Base::gameOver, this, &GameScene::gameOver);
    QObject::connect(&enemyRespawnTimer, &QTimer::timeout, this, &GameScene::spawnEnemy);
    QObject::connect(&bonusItemTimer, &QTimer::timeout, this, &GameScene::spawnBonus);
    gameTimer.start(FPS_REFRESH_DELTA);
    enemyRespawnTimer.start(ENEMY_RESPAWN_DELTA);
    bonusItemTimer.start(BONUS_RESPAWN_DELTA);
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

void GameScene::spawnEnemy()
{
    int rand_width;
    int rand_height;

    for (;;) {
        rand_width  = rand() % static_cast<int>(widthBrick * widthBrickCount);
        rand_height = rand() % static_cast<int>((heightBrick * heightBrickCount - 1));
        rand_height -= heightBrick;

        if(isCellAvaliable(rand_width, rand_height)) {
            break;
        }
    }

    QGraphicsPixmapItem *enemy = new QGraphicsPixmapItem(QPixmap(":/images/tank1up.png").scaled(widthBrick, heightBrick));
    addItem(enemy);
    enemy->setPos(rand_width, rand_height);
}

void GameScene::spawnBonus()
{

}

void GameScene::gameOver()
{
    //gameTimer.stop();

    GameOver *gameOverItem = new GameOver(QPointF(width()/2, height()/2));
    addItem(gameOverItem);
    gameOverItem->setPos(widthBrickCount / 2 * widthBrick - gameOverItem->pixmap().width()/2,
                         height());
    delete player;

    enemyRespawnTimer.stop();
    bonusItemTimer.stop();
}

bool GameScene::isCellAvaliable(int width, int height)
{
    QTransform t;
    auto leftTop = itemAt(QPointF(width, height), t);
    auto rightTop = itemAt(QPointF(width + widthBrick, height),t);
    auto leftBot = itemAt(QPointF(width, height + heightBrick), t);
    auto rightBot = itemAt(QPointF(width + widthBrick, height + heightBrick), t);
    auto center = itemAt(QPointF(width + widthBrick/2, height + heightBrick/2), t);


    return leftTop == nullptr && leftBot == nullptr
            && rightTop == nullptr && rightBot == nullptr && center == nullptr;
}



