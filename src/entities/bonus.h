#ifndef BONUS_H
#define BONUS_H

#include <QTimer>

#include "entity.h"

class Bonus : public Entity
{
    Q_OBJECT
public:
    enum Type : int {
      Shovel = 0,
      Granade,
      Star,
      Shield
    };
    explicit Bonus(int pixmapWidth, QGraphicsItem *parent = nullptr);

signals:
    void picked(Bonus::Type type);
private:
    QTimer *m_frameTimer;
    QTimer *m_remainingTimer;
    bool m_requireSwap {true};
    int m_pixmapWidth;
    Type m_type;
    QPixmap m_pixmap;
private:
    void changePixmap();
    void resetTimer();
    void init();
};

#endif // BONUS_H
