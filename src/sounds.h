#ifndef SOUNDS_H
#define SOUNDS_H

#include <QObject>
#include <QSound>

class Sounds : public QObject
{
    Q_OBJECT
public:
    Sounds();

    static void playShoot();
    static void playExplosion();
private:
    static QSound m_shoot;
    static QSound m_explosion;
};

#endif // SOUNDS_H
