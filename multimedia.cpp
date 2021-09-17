#include "multimedia.h"

Multimedia::Multimedia(QObject *parent) :
    QObject(parent),
    mPlayer(new QMediaPlayer(this))
{
    mPlaylist.addMedia(QUrl("qrc:/sounds/main.mp3"));
    mPlaylist.setPlaybackMode(QMediaPlaylist::Loop);

    moveToThread(&mThread);

    QObject::connect(&mThread, &QThread::started, this, &Multimedia::play);
}

void Multimedia::playMainTheme()
{
    mPlayer->setPlaylist(&mPlaylist);
    mPlayer->setVolume(100);
    mPlayer->play();
}

void Multimedia::play()
{
    mSound == Sound::Explosion ?
    QSound::play(":/sounds/explosion.wav") : QSound::play(":/sounds/shot.wav");
}

void Multimedia::playSound(Sound sound)
{
    mSound = sound;
    if (mThread.isRunning()) {
        mThread.wait();
    }

    mThread.start();
}
