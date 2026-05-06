#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

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
};

#endif // MYTCPSERVER_H
