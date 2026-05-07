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

OpeDB::~OpeDB()
{
    m_db.close();
}
