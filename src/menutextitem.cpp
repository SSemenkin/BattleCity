#include "menutextitem.h"

MenuTextItem::MenuTextItem()
{
    setFont(QFont(font().family(), font().pointSize() * 4));
}

MenuTextItem::MenuTextItem(const QString &text) :
    QGraphicsTextItem(text)
{
    setFont(QFont(font().family(), font().pointSize() * 4));
    updateTextColor();
}

void MenuTextItem::setState(bool state)
{
    m_state = state;
    updateTextColor();
}

bool MenuTextItem::getState() const
{
    return m_state;
}

void MenuTextItem::updateTextColor()
{
    m_state ? setDefaultTextColor(Qt::red) :
              setDefaultTextColor(Qt::white);
}

void MenuTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
    QGraphicsTextItem::mousePressEvent(event);
}

void MenuTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hovered();
    setState(true);
    updateTextColor();
    QGraphicsTextItem::hoverEnterEvent(event);
}
