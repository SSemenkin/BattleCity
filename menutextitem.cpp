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


