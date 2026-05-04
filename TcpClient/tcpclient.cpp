#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();
}

TcpClient::~TcpClient()
{
    delete ui;
}

//定义加载配置文件
void TcpClient::loadConfig()
{
    QFile file(":/client.config");
    //设置只读打开
    if(file.open(QIODevice::ReadOnly)){
        //全部读取,返回字节，添加头文件
        QByteArray data=file.readAll();
        //转化为字符串
        QString stdata=data.toStdString().c_str();

        file.close();
        stdata.replace("\r\n"," ");

        //通过空格分割
        QStringList stlist=stdata.split(" ");

        m_strIP=stlist[0];
        m_usPort=stlist[1].toUShort();

    }

    else{
        //错误提示
        QMessageBox::critical(this,"错误提示","配置文件打开失败");
    }
}
