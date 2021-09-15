#include "bonusitem.h"

BonusItem::BonusItem(Type type, QObject *parent) :
    QObject(parent)
{
    setZValue(2);
    switch (type) {

    }
}
