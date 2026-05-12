#ifndef PROTOCOL_H
#define PROTOCOL_H

//将总的长度定义为无符号整型
typedef unsigned int uint;
#define REGIST_OK "regist ok"
#define REGIST_FAILED "regist failed"


#define LOGIN_OK "login ok"
#define LOGIN_FAILED "login failed"
//将消息类型写成枚举类
enum ENUM_MSG_TYPE{
    ENUM_MSG_TYPE_MIN=0,
    ENUM_MSG_TYPE_REGiST_REQUEST,//注册请求
    ENUM_MSG_TYPE_REGIST_RESPOND,//回复类型
    ENUM_MSG_TYPE_LOGIN_REQUEST,
    ENUM_MSG_TYPE_LOGIN_RESPOND,

    ENUM_MSG_TYPE_ALL_ONLINE_REQUEST,//显示在线用户
    ENUM_MSG_TYPE_ALL_ONLINE_RESPOND,

    ENUM_MSG_TYPE_SEARCH_USR_REQUEST,//搜索用户
    ENUM_MSG_TYPE_SEARCH_USR_RESPOND,
    // ENUM_MSG_TYPE_RESPOND,
    // ENUM_MSG_TYPE_REQUEST,
    // ENUM_MSG_TYPE_RESPOND,
    ENUM_MSG_TYPE_MAX=0x00ffffff
};

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
