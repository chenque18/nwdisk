

# 说明
首先要使用qt提供的网络模块，在.pro文件中添加(一般在第一行)：
```pro
QT += widgets network
```
修改了 .pro 文件后，Qt Creator 或 VS Code 的构建系统不会自动立刻生效。你需要重新运行 qmake  

# 思路
加载配置文件，socket连接服务器，监听连接成功的信号，弹出消息框显示连接成功

# 代码实现
tcpclient.h
```cpp
//添加网络头文件
#include<QTcpSocket>

private:
    //需要连接服务器进行数据交互
    QTcpSocket m_tcpSocket;
```

tcpclient.cpp
```cpp
#include<QHostAddress>
//在构造函数中连接服务器
m_tcpSocket.connectToHost(QHostAddress(m_strIP),m_usPort);
//监听连接成功的信号
```

tcpclient.h
```cpp
public slots:
    //捕获连接信号槽函数
    void showConnect();
```

tcpclient.cpp
```cpp
//监听连接成功的槽函数
void TcpClient::showConnect()
{
    QMessageBox::information(this,"连接服务器","成功连接");
}

//在构造函数中连接信号和槽，注意connect放到m_tcpSocket.connectToHost(QHostAddress(m_strIP),m_usPort);之前
connect(&m_tcpSocket,&QTcpSocket::connected,this,&TcpClient::showConnect);
```

