#include "gamescene.h"

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    m_gameTimer(new QTimer(this)),
    m_bonusTimer(new QTimer(this)),
    m_enemySpawnTimer(new QTimer(this))
{
    calcRects();
    calcContants();
    setSceneRect(qApp->primaryScreen()->availableGeometry());
    setBackgroundBrush(QColor(128, 128, 128));
}

bool GameScene::loadLevel(const Level &level)
{
    bool result = level.isOk();
    if (result) {

        LevelStructure environment = level.levelStructure();

        m_lengthBlock = qMin(gameplayRect().height() / environment.size(),
                             gameplayRect().width() / environment.first().size());

        for (int i = 0; i < environment.size(); ++i) {
            for (int j = 0; j < environment.at(i).size(); ++j) {
                if (environment.at(i).at(j).toLatin1() != 32) {
                    StaticBody *body = new StaticBody(static_cast<StaticBody::Type>(environment.at(i).at(j).toLatin1() - '0'), m_lengthBlock);
                    addItem(body);
                    body->setPos(j * m_lengthBlock,
                                 i * m_lengthBlock);
                }
            }
        }

        initPlayer(level.playerPos());

        connect(m_gameTimer, &QTimer::timeout, this, &GameScene::advance);


        m_gameTimer->start(FPS_DELTA);
        m_enemySpawnTimer->start(ENEMY_RESPAWN_DELTA);
        m_bonusTimer->start(BONUS_RESPAWN_DELTA);

    }
    return result;
}

int GameScene::levelId() const
{
    return m_levelId;
}

QRectF GameScene::gameplayRect() const
{
    return m_gameplayRect;
}

QRectF GameScene::interfaceRect() const
{
    return m_interfaceRect;
}

void GameScene::gameOver()
{

}

void GameScene::calcRects()
{
    QRectF avaliableGeometry = qApp->primaryScreen()->availableGeometry();
    m_gameplayRect = avaliableGeometry.adjusted(0, 0, -avaliableGeometry.width()/4, 0);
    m_interfaceRect = avaliableGeometry.adjusted(3 * avaliableGeometry.width()/4, 0, 0, 0);
}

void GameScene::calcContants()
{
    FPS = 60;
    FPS_DELTA = 1000/FPS;
    ENEMY_RESPAWN_DELTA = BONUS_RESPAWN_DELTA =  6000;
}

void GameScene::initPlayer(const QPointF &pos)
{
    m_player = new PlayerTank(m_lengthBlock);
    addItem(m_player);
    m_player->setPos(pos.x() * m_lengthBlock,
                     pos.y() * m_lengthBlock);
}
