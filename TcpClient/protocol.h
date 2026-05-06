#ifndef PROTOCOL_H
#define PROTOCOL_H

//将总的长度定义为无符号整型
typedef unsigned int uint;

struct PDU
{
    uint uiPDULen;//总的协议数据单元大小
    uint uiMsgType;//消息类型
    char caData[64];//文件名
    uint uiMsgLen;//实际消息长度
    int caMsg[];//实际消息
};
PDU* makePDU(uint uiMsgLen);
#endif // PROTOCOL_H
