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
    setBackgroundBrush(QColor(126, 126, 126));
}

bool GameScene::loadLevel(const Level &level)
{
    bool result = level.isOk();
    if (result) {

        m_enemyCount = level.enemyCount();
        LevelStructure environment = level.levelStructure();

        m_lengthBlock = qMin(gameplayRect().height() / environment.size(),
                             gameplayRect().width() / environment.first().size());
        m_lastHeight = m_lengthBlock * environment.size();

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
        initInterface();


        QObject::connect(m_gameTimer,        &QTimer::timeout, this, &GameScene::advance);
        QObject::connect(m_enemySpawnTimer,  &QTimer::timeout, this, &GameScene::spawnEnemy);
        QObject::connect(m_bonusTimer,       &QTimer::timeout, this, &GameScene::spawnBonus);
        QObject::connect(m_base, &Base::destroyed, this, [this]()->void{
            m_base = nullptr;
            m_player->setRequireToDestroy();
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
    m_bonusTimer->stop();
    m_enemySpawnTimer->stop();

    GameOverItem *gameover = new GameOverItem(QPointF(gameplayRect().width()/2 - m_lengthBlock/2,
                                                    gameplayRect().height()/2 - m_lengthBlock/2));
    addItem(gameover);
    gameover->setPos(gameplayRect().width()/2 - gameover->pixmap().width()/2,
                     gameplayRect().height());
    QObject::connect(gameover, &GameOverItem::movedToCenter, this, &GameScene::toMenu);
}

void GameScene::gameWin()
{
    m_bonusTimer->stop();
    m_enemySpawnTimer->stop();
    emit toMenu();
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
    m_player->setBorderPoint(QPointF(gameplayRect().width(), m_lastHeight - m_lengthBlock));
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
    if (m_enemySpawned < m_enemyCount) {
        const QPointF spawnPos = getAvaliablePoint();
        Blink *blink = new Blink(m_lengthBlock);
        blink->setBorderPoint(m_player->borderPoint());
        addItem(blink);
        blink->setPos(spawnPos);
        blink->startAnimation();
        QObject::connect(blink, &Blink::enemyRespawned, this,[this](EnemyTank *enemy)->void{
           QObject::connect(enemy, &EnemyTank::destroyed, this, &GameScene::enemyDestroyed);
        });
        m_enemySpawned++;
    }
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
    hideEntityAndCreateConcrete(QPointF(basePoint.x() - m_lengthBlock, basePoint.y() + m_lengthBlock));
    hideEntityAndCreateConcrete(QPointF(basePoint.x(), basePoint.y() + m_lengthBlock));
    hideEntityAndCreateConcrete(QPointF(basePoint.x() + m_lengthBlock, basePoint.y() + m_lengthBlock));

    resetBorderTimers();
}

void GameScene::destroyAllEnemies()
{
    const auto allItems = items();
    for (int i = 0; i < allItems.size(); ++i) {
        Entity *entity = qgraphicsitem_cast<Entity*>(allItems.at(i));
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

void GameScene::initInterface()
{
    int initWidth = interfaceRect().x() + m_lengthBlock * 2;
    int initHeight = interfaceRect().y() + 10;

    for (int i = 0; i < m_enemyCount; ++i) {
        !(i % 2) ? initWidth -= m_lengthBlock :
                   initWidth += m_lengthBlock ;
        Entity *entity = new Entity(QPixmap(":images/enemy.png").scaled(m_lengthBlock, m_lengthBlock));
        addItem(entity);
        entity->setPos(initWidth, initHeight);
        if (i % 2 ) initHeight += m_lengthBlock;
        m_enemies.push_back(entity);
    }

    initWidth -= m_lengthBlock;

    QGraphicsTextItem *textItem = new QGraphicsTextItem("Score: ");
    textItem->setDefaultTextColor(Qt::white);
    addItem(textItem);
    textItem->setPos(initWidth, initHeight);

    m_scoreItems.push_back(new Entity(QPixmap(":/images/digits/0.png").scaled(m_lengthBlock/2, m_lengthBlock/2)));

    m_scoreY = initHeight + m_lengthBlock;
    m_scoreX = initWidth;

    showScore();
}

void GameScene::spawnExplosionAt(Entity *entity)
{
    Explosion *explosion = new Explosion(QPointF(entity->x() - entity->pixmap().width(),
                                         entity->y() - entity->pixmap().height()), entity->pixmap().width());
    addItem(explosion);
    explosion->startAnimation();
}

void GameScene::enemyDestroyed()
{
    m_score+=100;
    if (m_score  == m_enemyCount * 100) {
        gameWin();
    }
    rebuildScore();
    if (!m_enemies.isEmpty()) {
        m_enemies.last()->setRequireToDestroy();
        m_enemies.pop_back();
    }
}

void GameScene::rebuildScore()
{
    while(!m_scoreItems.isEmpty()) {
        m_scoreItems.first()->setRequireToDestroy();
        m_scoreItems.pop_front();
    }

    QVector<int> digits;
    int score = m_score;
    while(score) {
        digits.push_back(score % 10);
        score /= 10;
    }

    for (int i = 0; i < digits.size()/2; ++i)
        std::swap(digits[i], digits[digits.size() - 1 - i]);

    for (int i = 0; i < digits.size(); ++i) {
        m_scoreItems.push_back(new Entity(QPixmap(":/images/digits/"+QString::number(digits.at(i))+".png").scaled(
                                              m_lengthBlock/2, m_lengthBlock/2)));
    }
    showScore();
}

void GameScene::showScore()
{
    for (int i = 0 ; i < m_scoreItems.size(); ++i) {
        addItem(m_scoreItems.at(i));
        m_scoreItems.at(i)->setPos(m_scoreX + i * m_lengthBlock, m_scoreY);
    }
}

void GameScene::hideEntityAndCreateConcrete(const QPointF &nearPos)
{
    QTransform transform;
    QGraphicsItem *item = itemAt(QPointF(nearPos.x() + m_lengthBlock/2, nearPos.y() + m_lengthBlock/2), transform);

    Entity *entity = nullptr;
    if (item) {
        entity = qgraphicsitem_cast<Entity*>(item);
        if (entity && entity->entityName() == "StaticBody") {
            m_hides.push_back(entity);
            entity->hide();
        }
    }
    m_border.push_back(new StaticBody(StaticBody::Type::Concrete, m_lengthBlock));
    addItem(m_border.last());

    entity ? m_border.last()->setPos(entity->pos()) :
             m_border.last()->setPos(nearPos);
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
        p.setX(rand() % static_cast<int>(interfaceRect().width() - m_lengthBlock));
        p.setY(rand() % static_cast<int>(m_lastHeight - m_lengthBlock));

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

    bool iAtPos = true;
    for (int i = 0; i < m_border.size(); ++i) {
        if (itemAt(point, transform) == m_border.at(i)) {
            iAtPos = false;
            break;
        }
    }
    return !topLeft && !topRight && !leftBottom && !rightBottom && !center && iAtPos;
}
