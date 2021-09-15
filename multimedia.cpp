#include "multimedia.h"

Multimedia::Multimedia(QObject *parent) :
    QObject(parent),
    mPlayer(new QMediaPlayer(this))
{
    mPlaylist.addMedia(QUrl("qrc:/sounds/main.mp3"));
    mPlaylist.setPlaybackMode(QMediaPlaylist::Loop);
}

void Multimedia::playMainTheme()
{
    mPlayer->setPlaylist(&mPlaylist);
    mPlayer->setVolume(100);
    mPlayer->play();
}
