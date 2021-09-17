#ifndef MENUTEXTITEM_H
#define MENUTEXTITEM_H

#include <QGraphicsTextItem>
#include <QFont>

class MenuTextItem : public QGraphicsTextItem
{
public:
    explicit MenuTextItem(const QString &text,
                 QGraphicsItem *parent = nullptr);
    explicit MenuTextItem();

    void setCurrent(bool state);
    bool isCurrent() const;
private:
    bool mCurrent{false};
};

#endif // MENUTEXTITEM_H
