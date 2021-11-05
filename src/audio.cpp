#include "audio.h"

Audio *Audio::instance()
{
    static Audio audio;
    return &audio;
}

void Audio::playMain()
{
    m_player->play();
}

void Audio::stopMain()
{
    m_player->stop();
}

void Audio::playExplosion()
{
    m_explosion.play();
}

void Audio::playShoot()
{
    m_shoot.play();
}

Audio::Audio() :
    m_player(new QMediaPlayer),
    m_explosion(":/sounds/explosion.wav"),
    m_shoot(":/sounds/shoot.wav")
{
    m_playlist.addMedia(QUrl("qrc:/sounds/main.mp3"));
    m_playlist.setPlaybackMode(QMediaPlaylist::Loop);
    m_player->setPlaylist(&m_playlist);
}
