#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QApplication>
#include <QScreen>

#include "menutextitem.h"
#include "level.h"


class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);
    virtual ~MenuScene() noexcept;
    void initLevels(const QVector<Level> &levels);
    void toStartScreen();
    void toLevelScreen();
signals:
    void startGameAtLevel(int levelId);
    void quit();
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    MenuTextItem *m_play;
    MenuTextItem *m_quit;
    MenuTextItem *m_back;
    QVector<MenuTextItem*> m_levels;
    QGraphicsPixmapItem *m_logo;
    QVector<MenuTextItem*> m_lastDisplayed;
    QGraphicsPixmapItem *m_tankItem;
    int m_offset {20};
private:
    void onItemClicked();
    void onItemHovered();
    void hideLastShowedItems();
    void enterPressed();
    void changeCurrentButton(Qt::Key key);
    void deaktivateAllButNotSender();
    void moveTankToItem(QGraphicsItem *item);
};

#endif // MENUSCENE_H
