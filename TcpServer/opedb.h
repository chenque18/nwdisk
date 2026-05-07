#ifndef OPEDB_H
#define OPEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
class OpeDB : public QObject
{
    Q_OBJECT
public:
    explicit OpeDB(QObject *parent = nullptr);
    static OpeDB& getInstance();
    void init();
    ~OpeDB();//析构函数关闭数据库

signals:
public slots:
private:
    QSqlDatabase m_db;//连接数据库

};

#endif // OPEDB_H
