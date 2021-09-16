#include "player.h"

int Player::STAR_BONUS_DURATION = 10000; // 10 seconds;

Player::Player(const QPixmap &pixmap, QGraphicsItem *parent) :
    GraphicsPixmapObject(pixmap, parent)
{
    setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsFocusable);
    setFocus();
    setData(0, "Player");
    setData(1, 5); // helth
}

void Player::pickupBonus(BonusItem::BonusType bonusType)
{
    switch (bonusType) {
        case BonusItem::BonusType::Granade:
        {
            emit destroyEnemies();
            break;
        }
        case BonusItem::BonusType::Helmet:
        {
             createShield();
             break;
        }
        case BonusItem::BonusType::Shovel:
        {
             emit createBorder();
             break;
        }
        case BonusItem::BonusType::Star:
        {
             createStarBonus();
             break;
        }
    }
}

void Player::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        mDirection = newDirection(static_cast<Qt::Key>(e->key()));
        CURRENT_SPEED = PLAYER_MAX_SPEED;
        break;
    case Qt::Key_Space:
        fire();
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(e);
    }
}

void Player::keyReleaseEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        CURRENT_SPEED = 0;
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(e);
    }
}

bool Player::canDoNextStep(const QPointF &point) const
{
    QPointF basePoint = scenePos();
    basePoint.setX(basePoint.x() + point.x());
    basePoint.setY(basePoint.y() + point.y());
    auto l = scene()->itemAt(basePoint, sceneTransform());
    const QString objectType = l->data(0).toString();
    if (objectType == "Bonus") {
        l->setData(5, true);
    }
    return GraphicsPixmapObject::canDoNextStep(point);
}

void Player::advance(int phase)
{
    GraphicsPixmapObject::advance(phase);
    if (data(5).toBool() == true) {
        data(2).toBool() ? setData(5, false) : takeDamage();
    }
}

void Player::setRespawnPosition(const QPointF &respawnPoint)
{
    mRespawnPosition = respawnPoint;
    respawn();
}

void Player::createShield()
{
    if (data(2).toBool() == true) {
        shield.deinit();
    }
    shield.init(this);
    setData(2, true);
}

void Player::destroy()
{
    delete this;
}

void Player::takeDamage()
{
    int currHealth = data(1).toInt();
    currHealth = currHealth - 1;
    emit currentHealthChanged(currHealth);

    if (currHealth < 1) {
        destroy();
    } else {
        respawn();
        setData(1, currHealth);
    }
}

void Player::respawn()
{
    setPos(mRespawnPosition);
    setFocus();
    createShield();
}

void Player::createStarBonus()
{
    QTimer *starTimer = new QTimer(this);
    isStarBonus  = true;
    QObject::connect(starTimer, &QTimer::timeout, this, [this] () {
        isStarBonus = false;
    });
    starTimer->start(STAR_BONUS_DURATION);

}
