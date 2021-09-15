#include "level.h"

Level::Level(const QString &path)
{
    load(path);
}

Level::Level()
{

}

bool Level::isOk() const
{
    return mLevelID != -1;
}

bool Level::load(const QString &path)
{
    if (QFile::exists(path)) {
        QFile file(path);
        if (file.open(QIODevice::ReadOnly)) {
            QStringList rows = QString(file.readAll()).split("\r\n");
            fillPrivateData(rows);
            file.close();
            return true;
        } else return false;
    } else {
        return false;
    }
}

int Level::getLevelID() const
{
    return mLevelID;
}

matrix<int> Level::getLevelStructure() const
{
    return mStructure;
}

QPair<int, int> Level::getPlayerPosition() const
{
    return mPlayerPosition;
}

QPair<int, int> Level::getBasePosition() const
{
    return mBasePosition;
}

void Level::fillPrivateData(const QStringList &rows)
{
    mStructure.reserve(rows.size() - 1);
    mLevelID = rows.first().split(' ').first().toInt();

    QVector<int> rowContent;
    rowContent.reserve(rows.last().size());

    for (int i = 1; i < rows.size(); ++i) {
        if(rows.at(i).contains('p')) {
            mPlayerPosition = QPair<int,int>(rows.at(i).indexOf('p'), i - 1);
        }
        if (rows.at(i).contains('b')) {
            mBasePosition = QPair<int,int>(rows.at(i).indexOf('b'), i - 1);
        }

        for (int j = 0; j < rows.at(i).size(); ++j) {
            rowContent.push_back(rows.at(i).at(j).toLatin1());
        }
        mStructure.push_back(std::move(rowContent));
    }
}
