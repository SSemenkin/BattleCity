#ifndef STATICBODY_H
#define STATICBODY_H

#include <QTimer>

#include "entities/entity.h"

class StaticBody : public Entity
{
    Q_OBJECT
public:
    enum class Type : int8_t {
        Brick = 0,
        Bush,
        Concrete,
        Water
    };
    explicit StaticBody(Type type, int width);
private:
    void init();
    void changePixmap();
    void createTimer();
private:
    int m_width;
    Type m_type;
    bool m_requireSwapPixmap {true};
};

#endif // STATICBODY_H
