#include "mytcpsocket.h"
#include"opedb.h"
#include <QDebug>
#include<QString>
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
    //qDebug()<<pdu->uiMsgType<<(char*)(pdu->caMsg);
    switch(pdu->uiMsgType){
    case ENUM_MSG_TYPE_REGiST_REQUEST:{//注册请求
        char caName[32]={'\0'};
        char caPwd[32]={'\0'};
        strncpy(caName,pdu->caData,32);
        strncpy(caPwd,pdu->caData+32,32);
        bool ret=OpeDB::getInstance().handleRegist(caName,caPwd);
        PDU* respondPDU=makePDU(0);
        respondPDU->uiMsgType=ENUM_MSG_TYPE_REGIST_RESPOND;//注册回复类型
        if(ret)
        {
            strcpy(respondPDU->caData,REGIST_OK);
        }
        else{
            strcpy(respondPDU->caData,REGIST_FAILED);
        }
        write((char*)respondPDU,respondPDU->uiPDULen);
        free(respondPDU);
        respondPDU=NULL;
        break;


    }
    case ENUM_MSG_TYPE_LOGIN_REQUEST:{//登录请求
        char caName[32]={'\0'};
        char caPwd[32]={'\0'};
        strncpy(caName,pdu->caData,32);
        strncpy(caPwd,pdu->caData+32,32);
        bool ret=OpeDB::getInstance().handleLogin(caName,caPwd);
        PDU* respondPDU=makePDU(0);
        respondPDU->uiMsgType=ENUM_MSG_TYPE_LOGIN_RESPOND;
        if(ret)
        {
            strcpy(respondPDU->caData,LOGIN_OK);
        }
        else{
            strcpy(respondPDU->caData,LOGIN_FAILED);
        }
        write((char*)respondPDU,respondPDU->uiPDULen);
        free(respondPDU);
        respondPDU=NULL;
        break;

    }
    default:
        break;
    }
    free(pdu);
    pdu=NULL;


}
