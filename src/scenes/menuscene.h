#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);
signals:
    void startGameAtLevel(int levelId);
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MENUSCENE_H
