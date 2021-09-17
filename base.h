#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Base : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Base(const QPixmap& pixmap = QPixmap(":/images/base.png"), QObject *parent = nullptr);
    ///
    /// \brief position of Base represented as pair(x, y) separated on counter of blocks
    /// \return x, y position
    ///
    QPair<int, int> pseudoPos() const;

signals:
    ///
    /// \brief emits when Base destroyed
    ///
    void gameOver();

protected:
    void advance(int phase) override;
    bool isDelete {false};
};

#endif // BASE_H
