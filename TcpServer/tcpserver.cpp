#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "mytcpserver.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include<QHostAddress>
TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    loadConfig();
    MyTcpServer::getInstance().listen(QHostAddress(m_strIP),m_usPort);
}

//复制客户端的加载配置文件函数
void TcpServer::loadConfig()
{
    QFile file(":/server.config");
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data=file.readAll();
        QString stdata=data.toStdString().c_str();
        file.close();
        stdata.replace("\r\n"," ");
        QStringList stlist=stdata.split(" ");
        m_strIP=stlist[0];
        m_usPort=stlist[1].toUShort();
    }

    else{
        QMessageBox::critical(this,"错误提示","配置文件打开失败");
    }
}

TcpServer::~TcpServer()
{
    delete ui;
}
