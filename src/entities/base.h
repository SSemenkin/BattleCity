#ifndef BASE_H
#define BASE_H

#include <QGraphicsScene>

#include "entity.h"

class Base : public Entity
{
    Q_OBJECT
public:
    explicit Base(int width);

protected:
    virtual void advance(int phase) override;
};

#endif // BASE_H
