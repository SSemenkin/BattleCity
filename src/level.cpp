#include "level.h"

Level::Level(const QString &path)
{
    load(path);
}

int Level::levelId() const
{
    return m_levelId;
}

int Level::enemyCount() const
{
    return m_enemyCount;
}

QPointF Level::playerPos() const
{
    return m_playerPos;
}

QPointF Level::basePos() const
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
            Qt::CaseSensitivity sensitivity = Qt::CaseInsensitive;

            const QStringList fileContent = QString(file.readAll()).split(SEPARATOR);
            if (fileContent.isEmpty()) {
                qDebug() << "File " << path << " is empty";
                return;
            }
            m_levelId = fileContent.first().split(' ').first().toInt();
            m_enemyCount = fileContent.first().split(' ').at(1).toInt();

            m_levelStructure.reserve(fileContent.size() - 1);
            for(int i = 1; i < fileContent.size(); ++i) {
                m_levelStructure.push_back(fileContent.at(i));

                if (fileContent.at(i).contains('b', sensitivity)) {
                    m_basePos.setX(fileContent.at(i).indexOf('b', sensitivity));
                    m_basePos.setY(i - 1);
                }

                if (fileContent.at(i).contains('p', sensitivity)) {
                    m_playerPos.setX(fileContent.at(i).indexOf('p', sensitivity));
                    m_playerPos.setY(i - 1);
                }
            }

            file.close();
        } else {
            qDebug() << "Cannot open " << path << " file.\n" << file.errorString();
        }
    } else {
        qDebug() << "File " << path << " does not exists.";
    }
}
