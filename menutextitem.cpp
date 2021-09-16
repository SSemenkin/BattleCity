#include "menutextitem.h"


MenuTextItem::MenuTextItem(const QString &text, QGraphicsItem *parent) :
    QGraphicsTextItem(text, parent)
{
    setDefaultTextColor(Qt::white);
}


