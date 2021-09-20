﻿#ifndef LEVEL_H
#define LEVEL_H

#include <QFile>
#include <QPointF>
#include <QDebug>

using LevelStructure = QVector<QString>;

class Level
{
public:
    explicit Level(const QString &path);
    [[nodiscard]] int levelId() const;
    [[nodiscard]] QPointF getPlayerPos() const;
    [[nodiscard]] QPointF getBasePos() const;
    [[nodiscard]] bool isOk() const;
    [[nodiscard]] LevelStructure levelStructure() const;

private:
    int m_levelId {-1};
    QPointF m_invalidPos {-1, -1};
    QPointF m_playerPos;
    QPointF m_basePos;
    LevelStructure m_levelStructure;
private:
    void load(const QString &path);
};

#endif // LEVEL_H
