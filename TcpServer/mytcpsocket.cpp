#include "mytcpsocket.h"
#include <QDebug>

MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{
    connect(this,SIGNAL(readyRead()),this,SLOT(receiveMsg()));
}

void MyTcpSocket::receiveMsg()
{
    qDebug()<<this->bytesAvailable();
    uint uiPDULen=0;
    //先读出前4字节
    this->read((char*)&uiPDULen,sizeof(uint));
    //实际消息长度
    uint uiMsgLen=uiPDULen-sizeof(PDU);
    PDU*pdu=makePDU(uiMsgLen);
    //读取其余数据
    this->read((char*)pdu+sizeof(uint),uiPDULen-sizeof(uint));
    qDebug()<<pdu->uiMsgType<<(char*)(pdu->caMsg);

}
