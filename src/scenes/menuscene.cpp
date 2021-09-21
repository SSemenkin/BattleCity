#include "menuscene.h"

MenuScene::MenuScene(QObject *parent) : QGraphicsScene(parent),
    m_play(new MenuTextItem("Play")),
    m_quit(new MenuTextItem("Quit")),
    m_back(new MenuTextItem("Back")),
    m_logo(new QGraphicsPixmapItem(QPixmap(":/images/logo.png")))
{
    QObject::connect(m_play, &MenuTextItem::clicked, this, &MenuScene::onItemClicked);
    QObject::connect(m_back, &MenuTextItem::clicked, this, &MenuScene::onItemClicked);
    QObject::connect(m_quit, &MenuTextItem::clicked, this, &MenuScene::onItemClicked);

    QObject::connect(m_play, &MenuTextItem::hovered, this, &MenuScene::onItemHovered);
    QObject::connect(m_back, &MenuTextItem::hovered, this, &MenuScene::onItemHovered);
    QObject::connect(m_quit, &MenuTextItem::hovered, this, &MenuScene::onItemHovered);



    setSceneRect(qApp->primaryScreen()->availableGeometry());
    setBackgroundBrush(QColor(126, 126, 126));

    addItem(m_logo);
    m_logo->setPos(width()/2 - m_logo->pixmap().width()/2, 0);

    addItem(m_play);
    addItem(m_quit);
    addItem(m_back);
    m_back->hide();


    toStartScreen();

}

MenuScene::~MenuScene() noexcept
{
    delete m_play;
    delete m_quit;
    delete m_back;
    delete m_logo;

    while (!m_levels.isEmpty()) {
        delete m_levels.first();
        m_levels.pop_front();
    }
}

void MenuScene::initLevels(const QVector<Level> &levels)
{
    if (!m_levels.isEmpty()) return;

    for (int i = 0; i < levels.size(); ++i) {
        if (levels.at(i).isOk()) {
            MenuTextItem *level = new MenuTextItem(QString::number(i + 1) + " Level");
            QObject::connect(level, &MenuTextItem::clicked, this, &MenuScene::onItemClicked);
            QObject::connect(level, &MenuTextItem::hovered, this, &MenuScene::onItemHovered);

            m_levels.push_back(level);
            addItem(level);
            level->hide();
        }
    }
}

void MenuScene::toStartScreen()
{
    hideLastShowedItems();
    m_lastDisplayed.push_back(m_play);
    m_lastDisplayed.push_back(m_quit);

    m_play->show();
    m_quit->show();

    m_play->setPos(width()/2, m_logo->pixmap().height() + m_offset * 2);
    m_quit->setPos(width()/2, m_logo->pixmap().height() + m_offset * 5);
}

void MenuScene::toLevelScreen()
{
    hideLastShowedItems();


    int offset = m_offset * 2;
    for (int i = 0; i < m_levels.size(); ++i) {
        m_levels.at(i)->show();
        m_levels.at(i)->setPos(width()/2, m_logo->pixmap().height() + offset * (i + 2));
        m_lastDisplayed.push_back(m_levels.at(i));
    }
    m_lastDisplayed.push_back(m_back);

    m_back->show();
    m_back->setPos(width()/2, m_logo->pixmap().height() + offset * (m_levels.size() + 3));
}

void MenuScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Down:
        case Qt::Key_Up:
            changeCurrentButton(static_cast<Qt::Key>(event->key()));
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            enterPressed();
            break;
        default:
            QGraphicsScene::keyPressEvent(event);
            break;
    }
}

void MenuScene::onItemClicked()
{
    deaktivateAllButNotSender();
    enterPressed();
}

void MenuScene::onItemHovered()
{
    deaktivateAllButNotSender();
}

void MenuScene::hideLastShowedItems()
{
    while(!m_lastDisplayed.isEmpty()) {
        m_lastDisplayed.first()->hide();
        m_lastDisplayed.first()->setState(false);
        m_lastDisplayed.pop_front();
    }
}

void MenuScene::enterPressed()
{
    if (*m_play) {
        toLevelScreen();
    } else if (*m_quit) {
        emit quit();
    } else if (*m_back) {
        toStartScreen();
    } else {
        for (int i = 0; i < m_levels.size(); i++) {
            if (*m_levels.at(i)) {
                QString levelText = m_levels.at(i)->toPlainText();
                emit startGameAtLevel(levelText.midRef(0, levelText.indexOf(' ')).toInt() - 1);
                return;
            }
        }
    }
}

void MenuScene::changeCurrentButton(Qt::Key key)
{
    int value = key == Qt::Key_Up ? -1 : 1;

    int currIndex = -1;

    for (int i = 0; i < m_lastDisplayed.size(); ++i) {
        if (m_lastDisplayed.at(i)->getState()) {
            currIndex = i;
            break;
        }
    }

    if (currIndex == -1) {
        m_lastDisplayed.at(0)->setState(true);
    } else {
        m_lastDisplayed.at(currIndex)->setState(false);

        currIndex += value;

        if (currIndex == m_lastDisplayed.size()) {
            m_lastDisplayed.first()->setState(true);
        } else if (currIndex < 0){
            m_lastDisplayed.last()->setState(true);
        } else {
            m_lastDisplayed.at(currIndex)->setState(true);
        }
    }
}

void MenuScene::deaktivateAllButNotSender()
{
    QList<QGraphicsItem*> m_items = items();
    for (int i = 0; i < m_items.size(); ++i) {
        MenuTextItem *item = qgraphicsitem_cast<MenuTextItem*>(m_items.at(i));
        if (item) {
            item->setState(false);
        }
    }
    qobject_cast<MenuTextItem*>(sender())->setState(true);
}
