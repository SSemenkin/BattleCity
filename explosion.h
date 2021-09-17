#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>

class Explosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Explosion(QObject *parent = nullptr);
    void startAnimation();
    int frame() const {
        return mCurrentFrame;
    }
    void setFrame(int frame) {
        mCurrentFrame = frame;
    }
    ///
    /// \brief setFixedScenePos position where explosion is need to located for each frame
    /// \param fixedPos
    ///
    void setFixedScenePos(const QPointF& fixedPos);

signals:

private:
    static int mTimerDelta;
    int mCurrentFrame {0};
    QTimer *mTimer;
    QVector<QPixmap> mAnimationFrames;
    QPointF mCenterExplosion;
private:
    void onTimeout();
    void updateScenePosition();
};

#endif // EXPLOSION_H
