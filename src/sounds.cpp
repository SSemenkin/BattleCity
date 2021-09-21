#include "sounds.h"

QSound Sounds::m_shoot(":/sounds/shoot.wav");
QSound Sounds::m_explosion(":/sounds/explosion.wav");

Sounds::Sounds()
{

}

void Sounds::playShoot()
{
    m_shoot.play();
}

void Sounds::playExplosion()
{
    m_explosion.play();
}
