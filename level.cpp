#include "level.h"

Level::Level(const QString &path)
{
    if(!QFile::exists(path)) {
        qDebug() << "File " << path << "does not exists.";
        QCoreApplication::quit();
    }

    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QStringList rows = QString(file.readAll()).split("\r\n");
        file.close();

        m_matrix.reserve(rows.size());
        QVector<int> r;

        for (const QString& row : rows) {
            r.reserve(row.size());
            for (const QChar& c : row) {
                r.push_back(c.toLatin1());
            }
            m_matrix.push_back(std::move(r));

        }

    } else {
        qDebug() << "File " << path << " cannot be open.";
    }
}
