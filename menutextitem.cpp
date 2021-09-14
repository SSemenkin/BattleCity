#include "menutextitem.h"

QFont MenuTextItem::m_font = QFont("JetBrains Mono", 25);

MenuTextItem::MenuTextItem(const QString &text, QGraphicsItem *parent) :
    QGraphicsTextItem(text, parent)
{
    setDefaultTextColor(Qt::white);
    setFont(m_font);
}


