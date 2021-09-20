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
    setBackgroundBrush(QColor(47,79,79));
    //addRect(m_gameplayRect);
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
                if (i == environment.size() - 1 && j == environment.at(i).size() - 1) {
                    m_gameplayRect = QRectF(0, 0, j * m_lengthBlock + m_lengthBlock, i * m_lengthBlock + m_lengthBlock);
                }
            }
        }

        initPlayer(level.playerPos());

        QObject::connect(m_gameTimer,       &QTimer::timeout, this, &GameScene::advance);
        QObject::connect(m_enemySpawnTimer, &QTimer::timeout, this, &GameScene::spawnEnemy);
        QObject::connect(m_bonusTimer,      &QTimer::timeout, this, &GameScene::spawnBonus);

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
    m_player = new PlayerTank(m_lengthBlock - 4);
    addItem(m_player);
    m_player->setPos(pos.x() * m_lengthBlock,
                     pos.y() * m_lengthBlock);
    m_player->setBorderPoint(QPointF(m_gameplayRect.width(), m_gameplayRect.height()));
}

void GameScene::spawnEnemy()
{
    const QPointF spawnPos = getAvaliablePoint();
    Blink *blink = new Blink(m_lengthBlock);
    blink->setBorderPoint(m_player->borderPoint());
    addItem(blink);
    blink->setPos(spawnPos);
    blink->startAnimation();
}

void GameScene::spawnBonus()
{
    const QPointF spawnPos = getAvaliablePoint();
    Bonus *bonus = new Bonus(m_lengthBlock);
    addItem(bonus);
    bonus->setPos(spawnPos);

    QObject::connect(bonus, &Bonus::picked, m_player, &PlayerTank::pickupBonus);
}

QPointF GameScene::getAvaliablePoint() const
{
    QPointF p;

    for (;;) {
        p.setX(rand() % static_cast<int>(m_gameplayRect.width()));
        p.setY(rand() % static_cast<int>(m_gameplayRect.height()));

        if (isCellAvaliable(p)) {
            return p;
        }
    }
}

bool GameScene::isCellAvaliable(const QPointF &point) const
{
    QTransform transform;
    QGraphicsItem *topLeft = itemAt(point, transform);
    QGraphicsItem *topRight = itemAt(QPointF(point.x() + m_lengthBlock, point.y()), transform);
    QGraphicsItem *leftBottom = itemAt(QPointF(point.x(), point.y() + m_lengthBlock), transform);
    QGraphicsItem *rightBottom = itemAt(QPointF(point.x() + m_lengthBlock, point.y() + m_lengthBlock), transform);
    QGraphicsItem *center = itemAt(QPointF(point.x() + m_lengthBlock/2, point.y() + m_lengthBlock/2), transform);

    return !topLeft && !topRight && !leftBottom && !rightBottom && !center;
}
