#ifndef OPEDB_H
#define OPEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
class OpeDB : public QObject
{
    Q_OBJECT
public:
    explicit OpeDB(QObject *parent = nullptr);
    static OpeDB& getInstance();
    void init();
    bool handleRegist(const char* name,const char* pwd);
    bool handleLogin(const char* name,const char* pwd);
    void handleOFFline(const char* name);
    QStringList handleAllOnline();//
    ~OpeDB();//析构函数关闭数据库

signals:
public slots:
private:
    QSqlDatabase m_db;//连接数据库

};

#endif // OPEDB_H
