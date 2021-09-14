#include "multimedia.h"

Multimedia::Multimedia(QObject *parent) :
    QObject(parent),
    player(new QMediaPlayer(this))
{
    playlist.addMedia(QUrl("qrc:/sounds/main.mp3"));
    playlist.setPlaybackMode(QMediaPlaylist::Loop);
}

void Multimedia::playMainTheme()
{
    player->setPlaylist(&playlist);
    player->setVolume(100);
    player->play();
}
