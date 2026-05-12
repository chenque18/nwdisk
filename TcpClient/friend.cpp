#include "friend.h"
#include"protocol.h"
#include"tcpclient.h"


Friend::Friend(QWidget *parent)
    : QWidget{parent}
{
    m_pShowMsgTE = new QTextEdit;
    m_pFriendListWidget = new QListWidget;
    m_pInputMsgLE = new QLineEdit;

    m_pDelFriendPB = new QPushButton("删除好友");
    m_pFlushFriendPB = new QPushButton("刷新好友");
    m_pShowOnlineUsrPB = new QPushButton("显示在线");
    m_pSearchUsrPB = new QPushButton("查找用户");
    m_pMsgSendPB = new QPushButton("发送消息");
    m_pPrivateChatPB = new QPushButton("私聊");

    m_pOnline = new Online;
    //按钮垂直布局
    QVBoxLayout *pRightPBVBL = new QVBoxLayout;
    pRightPBVBL->addWidget(m_pDelFriendPB);
    pRightPBVBL->addWidget(m_pFlushFriendPB);
    pRightPBVBL->addWidget(m_pShowOnlineUsrPB);
    pRightPBVBL->addWidget(m_pSearchUsrPB);
    pRightPBVBL->addWidget(m_pPrivateChatPB);
    //聊天区 + 好友列表 + 按钮栏水平布局
    QHBoxLayout *pTopHBL = new QHBoxLayout;
    pTopHBL->addWidget(m_pShowMsgTE);
    pTopHBL->addWidget(m_pFriendListWidget);
    pTopHBL->addLayout(pRightPBVBL);

    QHBoxLayout *pMsgHBL = new QHBoxLayout;
    pMsgHBL->addWidget(m_pInputMsgLE);
    pMsgHBL->addWidget(m_pMsgSendPB);

    QVBoxLayout *pMain = new QVBoxLayout;
    pMain->addLayout(pTopHBL);
    pMain->addLayout(pMsgHBL);

    pMain->addWidget(m_pOnline);
    m_pOnline->hide();

    setLayout(pMain);
    connect(m_pShowOnlineUsrPB,SIGNAL(clicked()),this,SLOT(showOnline()));
}

void Friend::showAllOnlineUsr(PDU *pdu)
{
    if(pdu==nullptr){
        return;
    }
    m_pOnline->showUsr(pdu);
}



void Friend::showOnline()
{
    if(m_pOnline->isHidden()){
        m_pOnline->show();
        //产生socket
        PDU*pdu=makePDU(0);
        pdu->uiMsgType=ENUM_MSG_TYPE_ALL_ONLINE_REQUEST;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu,pdu->uiPDULen);
        free(pdu);
        pdu=nullptr;



    }
    else{
        m_pOnline->hide();
    }
}