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
    mGameTimer.stop();
    const Level level = levels[levelID];
    if(level.isOk()) {
        mCurrentLevel = levelID;
    }
    matrix<int> structure = level.getLevelStructure();

    if(structure.size()) {
        mHeightBrickCount = structure.size();
        mWidthBrickCount = structure.first().size();

        mHeightBrick = height() / structure.size();
        mWidthBrick = width() / structure.first().size();
        std::min(mHeightBrick, mWidthBrick) == mHeightBrick ? mWidthBrick = mHeightBrick :
                                                           mHeightBrick = mWidthBrick ;


        for (int i = 0 ; i < structure.size(); ++i) {
            for (int j = 0; j < structure.at(i).size(); ++j) {
                if (structure.at(i).at(j) != 32) {
                    StaticBlock *item = new StaticBlock(static_cast<StaticBlock::Type>(structure.at(i).at(j) - '0'), mWidthBrick);
                    addItem(item);
                    item->setPos(j * mWidthBrick, i * mHeightBrick);

                }
            }
        }
        initPlayer(level.getPlayerPosition());
        initBase(level.getBasePosition());
    }

    QObject::connect(&mGameTimer, &QTimer::timeout, this, &QGraphicsScene::advance);
    QObject::connect(mBase, &Base::gameOver, this, &GameScene::gameOver);
    QObject::connect(&mEnemyRespawnTimer, &QTimer::timeout, this, &GameScene::spawnEnemy);
    QObject::connect(&mBonusItemTimer, &QTimer::timeout, this, &GameScene::spawnBonus);
    mGameTimer.start(FPS_REFRESH_DELTA);
    mEnemyRespawnTimer.start(ENEMY_RESPAWN_DELTA);
    mBonusItemTimer.start(BONUS_RESPAWN_DELTA);
}

void GameScene::initPlayer(const QPair<int, int> &position)
{
    mPlayer = new Player;
    mPlayer->setPixmap(mPlayer->pixmap().scaled(mWidthBrick, mHeightBrick));
    addItem(mPlayer);
    mPlayer->setPos(position.first * mWidthBrick,
                    position.second * mHeightBrick);
}

void GameScene::initBase(const QPair<int, int> &position)
{
    mBase = new Base;
    mBase->setPixmap(mBase->pixmap().scaled(mWidthBrick, mHeightBrick));
    addItem(mBase);
    mBase->setPos(position.first * mWidthBrick,
                  position.second * mHeightBrick);
}

void GameScene::spawnEnemy()
{
    int rand_width;
    int rand_height;

    for (;;) {
        rand_width  = rand() % static_cast<int>(mWidthBrick * mWidthBrickCount);
        rand_height = rand() % static_cast<int>((mHeightBrick * mHeightBrickCount - 1));
        rand_height -= mHeightBrick;

        if(isCellAvaliable(rand_width, rand_height)) {
            break;
        }
    }

    // TODO init enemy at pos (x, y)
}

void GameScene::spawnBonus()
{

}

void GameScene::gameOver()
{
    //gameTimer.stop();

    GameOver *gameOverItem = new GameOver(QPointF(width()/2, height()/2));
    addItem(gameOverItem);
    gameOverItem->setPos(mWidthBrickCount / 2 * mWidthBrick - gameOverItem->pixmap().width()/2,
                         height());
    delete mPlayer;

    mEnemyRespawnTimer.stop();
    mBonusItemTimer.stop();
}

bool GameScene::isCellAvaliable(int width, int height)
{
    QTransform t;
    auto leftTop = itemAt(QPointF(width, height), t);
    auto rightTop = itemAt(QPointF(width + mWidthBrick, height),t);
    auto leftBot = itemAt(QPointF(width, height + mHeightBrick), t);
    auto rightBot = itemAt(QPointF(width + mWidthBrick, height + mHeightBrick), t);
    auto center = itemAt(QPointF(width + mWidthBrick/2, height + mHeightBrick/2), t);


    return leftTop == nullptr && leftBot == nullptr
            && rightTop == nullptr && rightBot == nullptr && center == nullptr;
}

