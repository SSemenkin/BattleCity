#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Base : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Base(const QPixmap& pixmap = QPixmap(":/images/base.png"), QObject *parent = nullptr);
    QPair<int, int> pseudoPos() const;

signals:
    void gameOver();

protected:
    void advance(int phase) override;
    void do_staff() = delete;
};

#endif // BASE_H
