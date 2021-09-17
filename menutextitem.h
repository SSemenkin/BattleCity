#ifndef MENUTEXTITEM_H
#define MENUTEXTITEM_H

#include <QGraphicsTextItem>
#include <QFont>

class MenuTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit MenuTextItem(const QString &text,
                 QGraphicsItem *parent = nullptr);
    explicit MenuTextItem();
    void setCurrent(bool state);
    bool isCurrent() const;
signals:
    void clicked(MenuTextItem *item);
private:
    bool mCurrent{false};

    // QGraphicsItem interface
protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MENUTEXTITEM_H
