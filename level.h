#ifndef LEVEL_H
#define LEVEL_H

#include <QFile>
#include <QCoreApplication>
#include <QDebug>

template <typename T>
using matrix = QVector<QVector<T>>;

class Level
{
public:

    explicit Level(const QString &path);
    Level();
    bool isOk() const;
    bool load(const QString &path);
    int getLevelID() const;
    matrix<int> getLevelStructure() const;
    QPair<int, int> getPlayerPosition() const;
    QPair<int, int> getBasePosition() const;


private:
    matrix<int> mStructure;
    QPair<int, int> mPlayerPosition;
    QPair<int, int> mBasePosition;
    int mLevelID{-1};

private:
    void fillPrivateData(const QStringList &rows);
};

#endif // LEVEL_H
