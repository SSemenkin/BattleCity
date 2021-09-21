#ifndef SCORE_H
#define SCORE_H

#include "entity.h"

class Score : public Entity
{
    Q_OBJECT
public:
    explicit Score(int pixmapWidth);
protected:
    void advance(int phase) override;
private:
    QTimer *m_remainingTimer;
};

#endif // SCORE_H
