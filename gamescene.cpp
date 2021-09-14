#include "gamescene.h"
#include <QTimer>

GameScene::GameScene(const Level &level, QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
    setSceneRect(qApp->primaryScreen()->availableGeometry());
    setSceneRect(0, 0, 1930, 1090);
    initLevelStructure(level);
}

void GameScene::initLevelStructure(const Level &level)
{
    matrix<int> structure = level.levelStructure();

    if(structure.size()) {

        int heightBrick = height() / structure.size();
        int widthBrick = width() / structure.first().size();

        static QPixmap brick(":/images/brick.png");
        brick = brick.scaled(widthBrick, heightBrick);

        for (int i = 0 ; i < structure.size(); ++i) {
            for (int j = 0; j < structure.at(i).size(); ++j) {
                if(structure.at(i).at(j) == 42) {
                    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(brick);
                    addItem(item);
                    item->setPos(j * widthBrick, i * heightBrick );
                }
            }
        }
    }
}
