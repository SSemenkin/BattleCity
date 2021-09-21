#ifndef MENUTEXTITEM_H
#define MENUTEXTITEM_H

#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QFont>

class MenuTextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit MenuTextItem();
    explicit MenuTextItem(const QString& text);

    void setState(bool state);
    bool getState() const;

    operator bool() const {
        return m_state;
    }

signals:
    void clicked();
    void hovered();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

private:
    bool m_state {false};

private:
    void updateTextColor();

};

#endif // MENUTEXTITEM_H
