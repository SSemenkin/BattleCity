#include "gamescene.h"

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    m_gameTimer(new QTimer(this)),
    m_bonusTimer(new QTimer(this)),
    m_enemySpawnTimer(new QTimer(this)),
    m_borderTimer(new QTimer(this)),
    m_borderBlinkTimer(new QTimer(this))
{
    calcRects();
    setSceneRect(qApp->primaryScreen()->availableGeometry());
    setBackgroundBrush(QColor(47,79,79));
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
        initBase(level.basePos());

        QObject::connect(m_gameTimer,        &QTimer::timeout, this, &GameScene::advance);
        QObject::connect(m_enemySpawnTimer,  &QTimer::timeout, this, &GameScene::spawnEnemy);
        QObject::connect(m_bonusTimer,       &QTimer::timeout, this, &GameScene::spawnBonus);
        QObject::connect(m_base, &Base::destroyed, this, [this]()->void{
            m_base = nullptr;
            gameOver();
        });
        QObject::connect(m_player, &PlayerTank::destroyed, this, [this]()->void{
            m_player = nullptr;
            gameOver();
        });

        QObject::connect(m_player, &PlayerTank::picked, this, &GameScene::playerPickedBonus);


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
    qDebug() << __PRETTY_FUNCTION__;
    m_bonusTimer->stop();
    m_enemySpawnTimer->stop();
    if (m_player) m_player->setRequireToDestroy();

    Entity *entity = new Entity(QPixmap(":/images/gameover.png").scaled(m_lengthBlock, m_lengthBlock));
    addItem(entity);
    entity->setPos(gameplayRect().width()/2 - entity->pixmap().width()/2,
                   gameplayRect().height()/2 - entity->pixmap().height()/2);
}

void GameScene::calcRects()
{
    QRectF avaliableGeometry = qApp->primaryScreen()->availableGeometry();
    m_gameplayRect = avaliableGeometry.adjusted(0, 0, -avaliableGeometry.width()/4, 0);
    m_interfaceRect = avaliableGeometry.adjusted(3 * avaliableGeometry.width()/4, 0, 0, 0);
}

void GameScene::initPlayer(const QPointF &pos)
{
    m_player = new PlayerTank(m_lengthBlock - 4);
    addItem(m_player);
    m_player->setRespawnPos(QPointF(pos.x() * m_lengthBlock, pos.y() * m_lengthBlock));
    m_player->setBorderPoint(QPointF(m_gameplayRect.width(), m_gameplayRect.height()));
}

void GameScene::initBase(const QPointF &pos)
{
    m_base = new Base(m_lengthBlock);
    addItem(m_base);
    m_base->setPos(pos.x() * m_lengthBlock,
                   pos.y() * m_lengthBlock);
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

void GameScene::spawnBorder()
{
    if (!m_base) return;
    const QPointF basePoint = m_base->scenePos();
    hideEntityAndCreateConcrete(QPointF(basePoint.x() + m_lengthBlock, basePoint.y()));
    hideEntityAndCreateConcrete(QPointF(basePoint.x() - m_lengthBlock, basePoint.y()));
    hideEntityAndCreateConcrete(QPointF(basePoint.x() + m_lengthBlock, basePoint.y() - m_lengthBlock));
    hideEntityAndCreateConcrete(QPointF(basePoint.x(), basePoint.y() - m_lengthBlock));
    hideEntityAndCreateConcrete(QPointF(basePoint.x() - m_lengthBlock, basePoint.y() - m_lengthBlock));


    resetBorderTimers();
}

void GameScene::destroyAllEnemies()
{
    for (QGraphicsItem *item : items()) {
        Entity *entity = qgraphicsitem_cast<Entity*>(item);
        if (entity && entity->entityName() == "Enemy") {
            spawnExplosionAt(entity);
            entity->setRequireToDestroy();
        }
    }
}

void GameScene::removeBorder()
{
    while(!m_border.isEmpty()) {
        m_border.first()->setRequireToDestroy();
        m_border.removeFirst();
    }

    while(!m_hides.isEmpty()) {
        m_hides.first()->show();
        m_hides.removeFirst();
    }

    QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::borderBlink);
    QObject::connect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);
}

void GameScene::startBorderBlinking()
{
    m_borderBlinkTimer->stop();
    QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);
    QObject::connect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::borderBlink);
    m_borderBlinkTimer->start(SWAP_PIXMAPS_DELTA);
}

void GameScene::borderBlink()
{
    for (int i = 0; i < m_border.size(); ++i) {
        m_border.at(i)->isVisible() ? m_border.at(i)->hide() : m_border.at(i)->show();
    }
}

void GameScene::resetBorderTimers()
{
    if(m_borderTimer->isActive()) {
        m_borderTimer->stop();
        m_borderBlinkTimer->stop();

        QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::borderBlink);
        QObject::disconnect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);


        for (int i = 0; i < m_border.size(); ++i) {
            m_border.at(i)->show();
        }
    }
    QObject::connect(m_borderBlinkTimer, &QTimer::timeout, this, &GameScene::startBorderBlinking);
    QObject::connect(m_borderTimer,      &QTimer::timeout, this, &GameScene::removeBorder);

    m_borderTimer->start(BONUS_DURATION);
    m_borderBlinkTimer->start(BONUS_DURATION - 2000);
}

void GameScene::spawnExplosionAt(Entity *entity)
{
    Explosion *explosion = new Explosion(QPointF(entity->x() - entity->pixmap().width(),
                                         entity->y() - entity->pixmap().height()), entity->pixmap().width());
    addItem(explosion);
    explosion->startAnimation();
}

void GameScene::hideEntityAndCreateConcrete(const QPointF &nearPos)
{
    QTransform transform;
    QGraphicsItem *item = itemAt(QPointF(nearPos.x() + m_lengthBlock/2, nearPos.y() + m_lengthBlock/2), transform);

    if (item) {
        Entity *entity = qgraphicsitem_cast<Entity*>(item);
        if (entity && entity->entityName() == "StaticBody") {
            m_hides.push_back(entity);
            entity->hide();

            m_border.push_back(new StaticBody(StaticBody::Type::Concrete, m_lengthBlock));
            addItem(m_border.last());
            m_border.last()->setPos(entity->scenePos());
        }
    }
}

void GameScene::playerPickedBonus(int bonus)
{
    Bonus::Type bonusType = static_cast<Bonus::Type>(bonus);
    if (bonusType == Bonus::Type::Granade) {
        destroyAllEnemies();
    } else if (bonusType == Bonus::Type::Shovel) {
        spawnBorder();
    }
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
