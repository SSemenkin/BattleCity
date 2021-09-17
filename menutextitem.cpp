#include "menutextitem.h"


MenuTextItem::MenuTextItem(const QString &text, QGraphicsItem *parent) :
    QGraphicsTextItem(text, parent)
{
    setDefaultTextColor(Qt::white);

    QFont newFont = font();
    newFont.setPointSize(newFont.pointSize() * 2);
    setFont(newFont);
}

MenuTextItem::MenuTextItem()
{
    setDefaultTextColor(Qt::white);

    QFont newFont = font();
    newFont.setPointSize(newFont.pointSize() * 2);
    setFont(newFont);
}

void MenuTextItem::setCurrent(bool state)
{
    mCurrent = state;
    mCurrent ? setDefaultTextColor(Qt::red) : setDefaultTextColor(Qt::white);
}

bool MenuTextItem::isCurrent() const
{
    return mCurrent;
}

void MenuTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCurrent(true);
    QGraphicsTextItem::hoverEnterEvent(event);
}

void MenuTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCurrent(false);
    QGraphicsTextItem::hoverLeaveEvent(event);
}

void MenuTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCurrent(event);
    emit clicked(this);
    QGraphicsTextItem::mousePressEvent(event);
}
