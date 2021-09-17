#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <QObject>
#include <QMediaPlayer>
#include <QSound>
#include <QMediaPlaylist>
#include <QSound>
#include <QThread>

class Multimedia : public QObject
{
    Q_OBJECT
public:

    enum class Sound {
        Explosion,
        Shot
    };

    explicit Multimedia(QObject *parent = nullptr);
    void playMainTheme();
    void playSound(Sound sound);

signals:

private:
    QMediaPlayer *mPlayer;
    QMediaPlaylist mPlaylist;

    Sound mSound;
    QThread mThread;

    void play();
};

#endif // MULTIMEDIA_H
