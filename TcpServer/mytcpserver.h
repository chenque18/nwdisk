#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include<QList>
//定义一个列表存放socket对象
#include"mytcpsocket.h"
#include <QTcpServer>


class MyTcpServer : public QTcpServer
{
    Q_OBJECT//为了使用信号和槽
public:
    MyTcpServer();
    //服务器监听函数
    static MyTcpServer &getInstance();
    //使用incomingConnection,只有发现客户端连接，自动调用函数
    void incomingConnection(qintptr socketDescriptor) override;
private:
    QList<MyTcpSocket*> m_tcpSocketList;
};

#endif // MYTCPSERVER_H
