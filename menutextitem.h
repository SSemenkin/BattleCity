#ifndef MENUTEXTITEM_H
#define MENUTEXTITEM_H

#include <QGraphicsTextItem>
#include <QFont>

class MenuTextItem : public QGraphicsTextItem
{
public:
    explicit MenuTextItem(const QString &text,
                 QGraphicsItem *parent = nullptr);

    inline void setCurrent(bool state) {
        mCurrent = state;
        mCurrent ? setDefaultTextColor(Qt::red) : setDefaultTextColor(Qt::white);
    }
    inline bool isCurrent() const {
        return mCurrent;
    }

private:

    bool mCurrent{false};
};

#endif // MENUTEXTITEM_H
