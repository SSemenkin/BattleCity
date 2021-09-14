#include "explosion.h"

int Explosion::mTimerDelta = 100;

Explosion::Explosion( QObject *parent) : QObject(parent)
{
    mAnimationFrames = {
        QPixmap(":/images/explosion/explosion1.png"),
        QPixmap(":/images/explosion/explosion2.png"),
        QPixmap(":/images/explosion/explosion3.png"),
        QPixmap(":/images/explosion/explosion4.png"),
        QPixmap(":/images/explosion/explosion5.png")
    };

    setPixmap(mAnimationFrames[mCurrentFrame++]);
}

void Explosion::startAnimation()
{
    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, &Explosion::onTimeout);
    mTimer->start(mTimerDelta);
}

void Explosion::onTimeout()
{
    setPixmap(mAnimationFrames[mCurrentFrame++]);
    if (mCurrentFrame == mAnimationFrames.size()) {
        mTimer->stop();
        delete this;
    }
}
