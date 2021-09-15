#include "explosion.h"

int Explosion::mTimerDelta = 70;

Explosion::Explosion( QObject *parent) : QObject(parent)
{
    mAnimationFrames = {
        QPixmap(":/images/explosion/explosion1.png"),
        QPixmap(":/images/explosion/explosion2.png"),
        QPixmap(":/images/explosion/explosion3.png"),
        QPixmap(":/images/explosion/explosion4.png"),
        QPixmap(":/images/explosion/explosion5.png")
    };
    setData(0, "Explosion");

    setPixmap(mAnimationFrames[mCurrentFrame++]);
}

void Explosion::startAnimation()
{
    updateScenePosition();
    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, &Explosion::onTimeout);
    mTimer->start(mTimerDelta);

}

void Explosion::setFixedScenePos(const QPointF &fixedPos)
{
    mCenterExplosion = fixedPos;
}

void Explosion::onTimeout()
{
    setPixmap(mAnimationFrames[mCurrentFrame++]);
    updateScenePosition();
    if (mCurrentFrame == mAnimationFrames.size()) {
        mTimer->stop();
        delete this;
    }
}

void Explosion::updateScenePosition()
{
    setPos(mCenterExplosion.x() - pixmap().width()/2, mCenterExplosion.y() - pixmap().height()/2);
}
