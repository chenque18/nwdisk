#include "mytcpserver.h"
#include<QDebug>
MyTcpServer::MyTcpServer() {

}

MyTcpServer &MyTcpServer::getInstance()
{
    static MyTcpServer instance;
    return instance;
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"new connected";
    MyTcpSocket*pTcpSocket=new MyTcpSocket;
    pTcpSocket->setSocketDescriptor(socketDescriptor);
    m_tcpSocketList.append(pTcpSocket);
    connect(pTcpSocket,SIGNAL(OFFline(MyTcpSocket*)),this,SLOT(deletesockeet(MyTcpSocket*)));

}

void MyTcpServer::deletesockeet(MyTcpSocket *mysocket)
{
    for(auto it=m_tcpSocketList.begin();it!=m_tcpSocketList.end();it++){
        if((*it)==mysocket){
            delete *it;//先删除mysocket
            *it=nullptr;
            m_tcpSocketList.erase(it);//再删除这个位置的指针
            break;
        }
    }
    //打印名字
    for(int i=0;i<m_tcpSocketList.size();i++){
        qDebug()<<m_tcpSocketList[i]->getname();
    }
}
