#ifndef SHIELD_H
#define SHIELD_H

#include "entity.h"

class Shield : public Entity
{
    Q_OBJECT
public:
    explicit Shield(QGraphicsItem *item, int pixmapWidth);
    void resetTimer();

private:
    QTimer *m_blinkTimer;
    QTimer *m_remainingTimer;
    bool m_swapRequire {true};
private:
    void swapPixmaps();
};

#endif // SHIELD_H
