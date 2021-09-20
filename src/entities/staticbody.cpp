#include "staticbody.h"


StaticBody::StaticBody(Type type, int width) :
    Entity(),
    m_width(width),
    m_type(type)
{
    init();
}

void StaticBody::init()
{
    switch (m_type) {
        case Type::Brick:
        {
            setPixmap(QPixmap(":/images/static_blocks/brick.png").scaled(m_width, m_width));
            setDestructible(true);
            setBulletCanMoveThroughObject(false);
            setActorCanMoveThroughObject(false);
            setLivesLeft(1);
            break;
        }
        case Type::Bush:
        {
            setPixmap(QPixmap(":/images/static_blocks/bush.png").scaled(m_width, m_width));
            setDestructible(false);
            setBulletCanMoveThroughObject(true);
            setActorCanMoveThroughObject(true);
            setLivesLeft(1);
            setZValue(2);
            break;
        }
        case Type::Concrete:
        {
            setPixmap(QPixmap(":/images/static_blocks/concrete.png").scaled(m_width, m_width));
            setDestructible(false);
            setBulletCanMoveThroughObject(false);
            setActorCanMoveThroughObject(false);
            setLivesLeft(1);
            break;
        }
        case Type::Water:
        {
            setDestructible(false);
            setBulletCanMoveThroughObject(true);
            setActorCanMoveThroughObject(false);
            setLivesLeft(1);
            setPixmap(QPixmap(":/images/static_blocks/water1.png").scaled(m_width, m_width));
            createTimer();
            break;
        }
    }
    setEntityName("StaticBody");
}

void StaticBody::changePixmap()
{
    m_requireSwapPixmap ? setPixmap(QPixmap(":/images/static_blocks/water2.png").scaled(m_width, m_width)):
                          setPixmap(QPixmap(":/images/static_blocks/water1.png").scaled(m_width, m_width));
    m_requireSwapPixmap = !m_requireSwapPixmap;
}

void StaticBody::createTimer()
{
    QTimer *timer = new QTimer(this);

    QObject::connect(timer, &QTimer::timeout, this, &StaticBody::changePixmap);

    timer->start(200);
}
