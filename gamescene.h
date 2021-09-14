#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QScreen>
#include <QApplication>

#include <QGraphicsPixmapItem>

#include "level.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(const Level &level = Level(":/levels/1_level.txt"), QObject *parent = nullptr);

private:
    void initLevelStructure(const Level &level);
};

#endif // GAMESCENE_H
