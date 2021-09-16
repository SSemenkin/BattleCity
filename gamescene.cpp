#include "gamescene.h"

int GameScene::FPS = 60;
int GameScene::FPS_REFRESH_DELTA = 1000/FPS;
int GameScene::ENEMY_RESPAWN_DELTA = 4000;
int GameScene::BONUS_RESPAWN_DELTA = 1000;

std::array<Level, 1> GameScene::levels = {
  Level(":/levels/1_level.txt")
};

GameScene::GameScene(int level, QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    loadLevel(level);
    setSceneRect(qApp->primaryScreen()->availableGeometry());
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
    QObject::connect(&mEnemyRespawnTimer, &QTimer::timeout, this, &GameScene::spawnBlink);
    QObject::connect(&mBonusItemTimer, &QTimer::timeout, this, &GameScene::spawnBonus);
    QObject::connect(mPlayer, &Player::createBorder, this, &GameScene::createBorderAroundBase);
    mGameTimer.start(FPS_REFRESH_DELTA);
    mEnemyRespawnTimer.start(ENEMY_RESPAWN_DELTA);
    mBonusItemTimer.start(BONUS_RESPAWN_DELTA);

}

void GameScene::initPlayer(const QPair<int, int> &position)
{
    mPlayer = new Player;
    mPlayer->setPixmap(mPlayer->pixmap().scaled(mWidthBrick - 1, mHeightBrick - 1));
    addItem(mPlayer);
    mPlayer->setPos(position.first * mWidthBrick,
                    position.second * mHeightBrick );
}

void GameScene::initBase(const QPair<int, int> &position)
{
    mBase = new Base;
    mBase->setPixmap(mBase->pixmap().scaled(mWidthBrick, mHeightBrick));
    addItem(mBase);
    mBase->setPos(position.first * mWidthBrick,
                  position.second * mHeightBrick);
}

void GameScene::spawnBlink()
{
    auto point = getRandomAndAvaliableCell();

    Blink *blink = new Blink(mWidthBrick);

    addItem(blink);
    blink->setPos(point.first, point.second);
    blink->startAnimation();
}

void GameScene::spawnBonus()
{
    auto point = getRandomAndAvaliableCell();

    int randomBonus = rand() % 4;

    BonusItem *item = new BonusItem(static_cast<BonusItem::BonusType>(randomBonus), mWidthBrick);
    addItem(item);

    item->setPos(point.first,
                 point.second);
    QObject::connect(item, &BonusItem::picked, mPlayer, &Player::pickupBonus);

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

QPair<int, int> GameScene::getRandomAndAvaliableCell() const
{
    int rand_width;
    int rand_height;

    for (;;) {
        rand_width  = rand() % static_cast<int>(mWidthBrick * mWidthBrickCount);
        rand_height = rand() % static_cast<int>((mHeightBrick * mHeightBrickCount - 1));
        rand_height -= mHeightBrick;

        if(isCellAvaliable(rand_width, rand_height)) {
           return QPair<int, int> (rand_width, rand_height);
        }
    }
}


bool GameScene::isCellAvaliable(int width, int height) const
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

void GameScene::createBorderAroundBase()
{
   auto pos = mBase->pos();

   removeItemAndCreateSteel(pos.x() + mWidthBrick, pos.y());
   removeItemAndCreateSteel(pos.x() + mWidthBrick, pos.y() - mHeightBrick);
   removeItemAndCreateSteel(pos.x(), pos.y() - mHeightBrick);
   removeItemAndCreateSteel(pos.x() - mWidthBrick, pos.y() - mHeightBrick);
   removeItemAndCreateSteel(pos.x() - mWidthBrick, pos.y());

}

void GameScene::removeItemAndCreateSteel(int x, int y)
{
    QGraphicsItem *item = itemAt(x+mWidthBrick/2,y+mWidthBrick/2, QTransform());
    if (item && (item->data(0).toString() == "StaticBody" ||
            item->data(0).toString() == "Bonus")) {
        item->setData(5, true);
    }

    StaticBlock *steel = new StaticBlock(StaticBlock::Type::Concrete, mWidthBrick);
    addItem(steel);
    steel->setPos(x, y);
}

