

# TCP服务器搭建
加载配置文件，QTcpServer监听客户端连接，捕获连接信号槽函数

# 新建Qt项目
命名为tcpServer，基类选择QWidget，类名改为TcpServer  
把客户端的client.config文件复制到服务器项目目录下，添加到资源文件中，命名为config.qrc  
client.config文件内容不变，改名为server.config  

#
在项目中添加c++ Class文件，类名MyTcpServer，基类选择QTcpServer，之后会报错没有找到类,在pro中添加
```cpp
#添加网络模块
QT += widgets network
```

# 支持信号和槽
要在类定义中添加Q_OBJECT宏，mytcpserver.h文件内容如下：
mytcpserver.h
```cpp
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT//为了使用信号和槽
public:
    MyTcpServer();
};

#endif // MYTCPSERVER_H
```

# 实现服务器监听
mytcpserver.h
```cpp
public:
    //服务器监听函数
    static MyTcpServer &getInstance();
```
mytcpserver.cpp
```cpp
MyTcpServer &MyTcpServer::getInstance()
{
    static MyTcpServer instance;
    return instance;
}
```
tcpserver.cpp
```cpp
#include "mytcpserver.h"

//在构造函数中监听
MyTcpServer::getInstance().listen();
```
监听需要ip和port，把TcpClient项目中的loadConfig函数复制到TcpServer项目
tcpserver.h
```cpp

public:
    //初始化加载配置文件
    void loadConfig();
private:
    //存放ip和port
    QString m_strIP;
    quint16 m_usPort;
```

tcpserver.cpp别忘了修改作用域,加头文件,构造函数中调用loadConfig函数
```cpp
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include<QFile>
#include<QHostAddress>//之前忘了添加这个头文件，在tcpclient.cpp中也要添加了这个头文件
void TcpServer::loadConfig()
{
    QFile file(":/server.config");//注意路径和文件名  
    if(file.open(QIODevice::ReadOnly)){
        QByteArray data=file.readAll();
        QString stdata=data.toStdString().c_str();       
        file.close();
        stdata.replace("\r\n"," ");
        QStringList stlist=stdata.split(" ");
        m_strIP=stlist[0];
        m_usPort=stlist[1].toUShort();
        qDebug()<<m_strIP;//测试
        qDebug()<<m_usPort;  
    }
    else{
        QMessageBox::critical(this,"错误提示","配置文件打开失败");
    }
}
```
# 完善监听
tcpserver.cpp
```cpp
MyTcpServer::getInstance().listen(QHostAddress(m_strIP),m_usPort);
//点击listen按f2查看参数类型

```

mytcpserver.h
```cpp
public:
    //使用incomingConnection,只要发现客户端连接，自动调用函数
    void incomingConnection(qintptr socketDescriptor) override;
    //这个是虚函数，需要重写
```

mytcpserver.cpp
```cpp
#include<QDebug>
void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    //有新连接自动打印
    qDebug()<<"new connected";
}
```
# 补充知识点
## 37-51行使用单例模式，核心是一个类在整个程序运行期间，永远只存在唯一的一个实例，并且提供一个可以全局访问它的入口。  
一个 TCP 服务器通常只需要监听一个固定的端口  
语法:  
.h
```cpp
static 类名::&函数名();
```
.cpp
```cpp
返回类型& 类名::函数名()
{
    static 类名 instance;
    return instance;
}
```














