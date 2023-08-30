#ifndef SQL_MANAGER_H
#define SQL_MANAGER_H

#include <QString>
#include <QVector>
#include <QtSql/QSqlDatabase>


class SqlManager {
public:
    SqlManager();
    ~SqlManager();

    static SqlManager *instance;
    static SqlManager *getInstance() {
        if (instance == nullptr) {
            instance = new SqlManager();
        }
        return instance;
    }

    bool init();

    // 获取元件
    QVector<QStringList> getComponents(QString strCondition = "");

    // 增加元件
    void addComponents(QVector<QStringList>);

    // 修改元件
    void updateComponents(QStringList);

    // 删除元件
    void delComponents(QString id);

private:
    QSqlDatabase m_db;
};


#endif //SQL_MANAGER_H
