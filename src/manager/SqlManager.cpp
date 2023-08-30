#include "SqlManager.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QStringList>
#include <QSettings>

SqlManager *SqlManager::instance = nullptr;

SqlManager::SqlManager()
{
}

SqlManager::~SqlManager()
{

}

bool SqlManager::init() {

    QString path;
    QSettings *configs = new QSettings("config/config.ini", QSettings::IniFormat);
    path = configs->value("url/db").toString();
    delete configs;

    qDebug() << QSqlDatabase::drivers();
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.QSqlDatabase::setDatabaseName(path);
    qDebug() << path;
    return m_db.open();
}

QVector<QStringList> SqlManager::getComponents(QString strCondition)
{
    QSqlQuery query(m_db);
    QString strsql = QString("select * from componentBox %1").arg(strCondition);

    qDebug() << strsql;
    QVector<QStringList> vec;
    bool ret = query.exec(strsql);
    if (!ret) {
        qDebug() << query.lastError().text();
    } else {
        int cols = query.record().count();
        QStringList list;

        while(query.next()) {
            list.clear();
            for(int i = 0; i < cols; i++) {
                list << query.value(i).toString();
            }
            vec.push_back(list);
        }
    }
    return vec;
}

void SqlManager::delComponents(QString id)
{
    QSqlQuery query(m_db);
    QString strsql = QString("delete from componentBox where id=%1").arg(id);
    QVector<QStringList> vec;
    bool ret = query.exec(strsql);

    if (!ret) {
        qDebug() << query.lastError().text();
    } else {
        int cols = query.record().count();
        QStringList list;

        while(query.next()) {
            list.clear();
            for(int i = 0; i < cols; i++) {
                list << query.value(i).toString();
            }
            vec.push_back(list);
        }
    }
}

void SqlManager::addComponents(QVector<QStringList> vec)
{
    if (vec.size() == 0) {
        return;
    }
    auto list = vec[0];
    QSqlQuery query(m_db);
    QString strsql = QString("INSERT INTO componentBox (id, value, codeName, footPrint, other1, other2, other3, boxName, lineNumber, columnNumber, jlcNumber) "
                             "VALUES (null, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10') ")

        .arg(list[1])
        .arg(list[2])
        .arg(list[3])
        .arg(list[4])
        .arg(list[5])
        .arg(list[6])
        .arg(list[7])
        .arg(list[8])
        .arg(list[9])
        .arg(list[10]);

    qDebug() << strsql;
    bool ret = query.exec(strsql);
    if (!ret) {
        qDebug() << query.lastError().text();
    }

}
void SqlManager::updateComponents(QStringList list)
{
    QSqlQuery query(m_db);
    QString strsql = QString("UPDATE componentBox set value='%2', codeName='%3', "
                             "footPrint='%4', other1='%5', "
                             "other2='%6', other3='%7', "
                             "boxName='%8', lineNumber='%9', jlcNumber='%11', "
                             "columnNumber='%10' where id= '%1'")

        .arg(list[0])
        .arg(list[1])
        .arg(list[2])
        .arg(list[3])
        .arg(list[4])
        .arg(list[5])
        .arg(list[6])
        .arg(list[7])
        .arg(list[8])
        .arg(list[9])
        .arg(list[10]);


    qDebug() << strsql;
    bool ret = query.exec(strsql);
    if (!ret) {
        qDebug() << query.lastError().text();
    }
}
