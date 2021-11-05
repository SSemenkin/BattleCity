#ifndef AUDIO_H
#define AUDIO_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>


class Audio
{
public:
    static Audio* instance();
    void playMain();
    void stopMain();
    void playExplosion();
    void playShoot();

private:
    Audio(const Audio&) = delete;
    Audio(Audio&&) = delete;
    Audio& operator=(const Audio&) = delete;
    Audio& operator=(Audio&&) = delete;
    Audio();

    std::unique_ptr<QMediaPlayer> m_player;
    QMediaPlaylist m_playlist;

    QSound m_explosion;
    QSound m_shoot;
};

#endif // AUDIO_H
