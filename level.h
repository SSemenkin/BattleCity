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
    Level(const QString &path);

    matrix<int> levelStructure() const {
        return m_matrix;
    }

    int id() const {
        return m_id;
    }

private:
    matrix<int> m_matrix;
    int m_id {1};
};

#endif // LEVEL_H
