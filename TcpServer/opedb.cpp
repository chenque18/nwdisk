#include "opedb.h"
#include<QMessageBox>

#include<QSqlError>
OpeDB::OpeDB(QObject *parent)
    : QObject{parent}
{

   m_db=QSqlDatabase::addDatabase("QMYSQL");
}

OpeDB &OpeDB::getInstance()
{
    static OpeDB instance;
    return instance;
}

void OpeDB::init()
{
    m_db.setHostName("172.20.10.2");
    m_db.setDatabaseName("snetwork_disk");
    m_db.setUserName("root");         // 填入您的 MySQL 用户名，通常是 root
    m_db.setPassword("123456");  // 填入您的 MySQL 密码
    if(m_db.open()){
        QSqlQuery query;
        query.exec("select * from usrinfo");
        while(query.next())
        {
            QString data = QString("%1, %2, %3, %4").arg(query.value(0).toString()).arg(query.value(1).toString())
            .arg(query.value(2).toString()).arg(query.value(3).toString());
            qDebug() << data;
        }

    }
    else{
        qDebug() << "数据库连接失败，原因: " << m_db.lastError().text();
        QMessageBox::critical(NULL,"打开数据库","打开失败");
    }
}

bool OpeDB::handleRegist(const char *name, const char *pwd)
{
    if(name==nullptr || pwd==nullptr)
    {
        return false;
    }
    //使用sql语句写入
    QString data=QString("insert into usrinfo(name,pwd) values('%1','%2')").arg(name).arg(pwd);
    QSqlQuery query;
    return query.exec(data);
}

bool OpeDB::handleLogin(const char *name, const char *pwd)
{
    if(name==nullptr || pwd==nullptr)
    {
        return false;
    }
    QString data=QString("select *from usrinfo where name='%1' and pwd='%2' and online=0").arg(name).arg(pwd);
    QSqlQuery query;
    query.exec(data);
    if(query.next()){//看看有没有记录
        //如果有记录，说明登录成功，修改在线状态
        QString updata=QString("update usrinfo set online=1 where name='%1'").arg(name);
        query.exec(updata);
        return true;
    }
    else{
        return false;
    }
}

void OpeDB::handleOFFline(const char *name)
{
    if(name==nullptr)
    {
        qDebug()<<"名字为空";
        return;
    }
    QString data=QString("update usrinfo set online=0 where name='%1'").arg(name);
    QSqlQuery query;
    query.exec(data);

}

QStringList OpeDB::handleAllOnline()
{
    QString data=QString("select name from usrinfo where online=1");
    QSqlQuery query;
    query.exec(data);

    QStringList result;
    result.clear();
    while(query.next()){//查询结果有多行，循环读取
        result.append(query.value(0).toString());
    }
    return result;
}

OpeDB::~OpeDB()
{
    m_db.close();
}
