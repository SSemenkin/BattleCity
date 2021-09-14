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
    QMediaPlayer *player;
    QMediaPlaylist playlist;
};

#endif // MULTIMEDIA_H
