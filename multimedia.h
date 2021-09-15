#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <QObject>
#include <QMediaPlayer>
#include <QSound>
#include <QMediaPlaylist>

class Multimedia : public QObject
{
    Q_OBJECT
public:
    explicit Multimedia(QObject *parent = nullptr);
    void playMainTheme();

signals:

private:
    QMediaPlayer *mPlayer;
    QMediaPlaylist mPlaylist;
};

#endif // MULTIMEDIA_H
