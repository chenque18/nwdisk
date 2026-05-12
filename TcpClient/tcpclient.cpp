#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>
#include<QHostAddress>

#include"opewidget.h"
#include "protocol.h"
TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    this->setFixedSize(370,350);
    loadConfig();
    //连接服务器
    //其他写法：
    //connect(&m_tcpSocket,&QTcpSocket::connected,this,&TcpClient::showConnect);
    
    connect(&m_tcpSocket,SIGNAL(connected()),this,SLOT(showConnect()));
    connect(&m_tcpSocket,SIGNAL(readyRead()),this,SLOT(receivemsg()));
    m_tcpSocket.connectToHost(QHostAddress(m_strIP),m_usPort);
    
}

TcpClient::~TcpClient()
{
    delete ui;
}

//加载配置文件函数
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

TcpClient &TcpClient::getInstance()
{
    static TcpClient instance;
    return instance;
}

QTcpSocket &TcpClient::getTcpSocket()
{
    return m_tcpSocket;
}

//提示连接的槽函数
void TcpClient::showConnect()
{
    QMessageBox::information(this,"连接服务器","成功连接");
}

void TcpClient::receivemsg()
{
    qDebug()<<m_tcpSocket.bytesAvailable();
    uint uiPDULen=0;
    //先读出前4字节
    m_tcpSocket.read((char*)&uiPDULen,sizeof(uint));
    //实际消息长度
    uint uiMsgLen=uiPDULen-sizeof(PDU);
    PDU*pdu=makePDU(uiMsgLen);
    //读取其余数据
    m_tcpSocket.read((char*)pdu+sizeof(uint),uiPDULen-sizeof(uint));
    //qDebug()<<pdu->uiMsgType<<(char*)(pdu->caMsg);
    switch(pdu->uiMsgType){
    case ENUM_MSG_TYPE_REGIST_RESPOND:{//回复类型
        if(0==strcmp(pdu->caData,REGIST_OK)){
            QMessageBox::information(this,"注册","成功");
            }
        else if(0==strcmp(pdu->caData,REGIST_FAILED)){
            QMessageBox::warning(this,"注册","用户名已存在，注册失败");

            }
        break;
    }

    case ENUM_MSG_TYPE_LOGIN_RESPOND:{//登录回复类型
        if(0==strcmp(pdu->caData,LOGIN_OK)){
            QMessageBox::information(this,"登录","成功");
            OpeWidget::getInstance().show();
            this->hide();

        }
        else if(0==strcmp(pdu->caData,LOGIN_FAILED)){
            QMessageBox::warning(this,"登录","失败");

        }
        break;
    }
    case ENUM_MSG_TYPE_ALL_ONLINE_RESPOND:{
        OpeWidget::getInstance().getFriend()->showAllOnlineUsr(pdu);//获得好友界面
        break;
    }




    default:
        break;
    }
    free(pdu);
    pdu=NULL;

}


#if 0
void TcpClient::on_send_pb_clicked()
{
    QString strMsg=ui->lineEdit->text();
    //如果输入框是空的，不发送
    if(strMsg.isEmpty()){
        QMessageBox::warning(this,"信息发送","发送的信息不能为空");
    }
    else{
        PDU*pdu=makePDU(strMsg.size());
        pdu->uiMsgType=8888;
        memcpy(pdu->caMsg,strMsg.toStdString().c_str(),strMsg.size());
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu=NULL;
    }
}
#endif

void TcpClient::on_login_btn_clicked()
{
    QString strname=ui->name_edit->text();
    QString strpwd=ui->pwd_edit->text();
    if(!strname.isEmpty() && !strpwd.isEmpty())//都不为空
    {
        PDU*pdu=makePDU(0);
        pdu->uiMsgType=ENUM_MSG_TYPE_LOGIN_REQUEST; //登录请求
        strncpy(pdu->caData,strname.toStdString().c_str(),32);
        strncpy(pdu->caData+32,strpwd.toStdString().c_str(),32);
        //通过socket发送
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu=NULL;
    }else{
        QMessageBox::warning(this,"错误","登录失败:用户名或密码不能为空");
    }
}


void TcpClient::on_regist_btn_clicked()
{
    QString strname=ui->name_edit->text();
    QString strpwd=ui->pwd_edit->text();
    if(!strname.isEmpty() && !strpwd.isEmpty())//都不为空
    {
        PDU*pdu=makePDU(0);
        pdu->uiMsgType=ENUM_MSG_TYPE_REGiST_REQUEST; //注册请求
        strncpy(pdu->caData,strname.toStdString().c_str(),32);
        strncpy(pdu->caData+32,strpwd.toStdString().c_str(),32);
        //通过socket发送
        m_tcpSocket.write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu=NULL;
    }else{
        QMessageBox::warning(this,"错误","注册失败:用户名或密码不能为空");
    }
}


void TcpClient::on_logout_clicked()
{

}

