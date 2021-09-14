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
        current = state;
        current ? setDefaultTextColor(Qt::red) : setDefaultTextColor(Qt::white);
    }
    inline bool isCurrent() const {
        return current;
    }

private:
    static QFont m_font;

    bool current{false};
};

#endif // MENUTEXTITEM_H
