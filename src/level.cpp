#include "level.h"

Level::Level(const QString &path)
{
    load(path);
}

int Level::levelId() const
{
    return m_levelId;
}

QPointF Level::getPlayerPos() const
{
    return m_playerPos;
}

QPointF Level::getBasePos() const
{
    return m_basePos;
}

bool Level::isOk() const
{
    return m_levelId != -1 && m_playerPos != m_invalidPos
            && m_basePos != m_invalidPos;
}

LevelStructure Level::levelStructure() const
{
    return m_levelStructure;
}

void Level::load(const QString &path)
{
#ifdef WIN32
    #define SEPARATOR "\r\n"
#else
    SEPARATOR "\n"
#endif
    QFile file(path);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            const QStringList fileContent = QString(file.readAll()).split(SEPARATOR);
            if (fileContent.isEmpty()) {
                qDebug() << "File " << path << " is empty";
                return;
            }
            m_levelId = fileContent.first().split(' ').first().toInt();

            m_levelStructure.reserve(fileContent.size() - 1);
            for(int i = 1; i < fileContent.size(); ++i) {
                m_levelStructure.push_back(fileContent.at(i));
            }

            file.close();
        } else {
            qDebug() << "Cannot open " << path << " file.\n" << file.errorString();
        }
    } else {
        qDebug() << "File " << path << " does not exists.";
    }
}
