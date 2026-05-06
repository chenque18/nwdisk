
#include"protocol.h"
#include <stdlib.h>
#include <string.h>

PDU *makePDU(uint uiMsgLen)
{
    //计算总长度 (固定头大小 + 实际负载大小)
    uint uiPDULen=sizeof(PDU)+uiMsgLen;
     //动态分配内存给pdu
    PDU *pdu=(PDU*)malloc(uiPDULen);
    if(pdu==NULL){
        exit(EXIT_FAILURE);
    }
    memset(pdu,0,uiPDULen);
    pdu->uiMsgLen = uiMsgLen;
    pdu->uiPDULen = uiPDULen;
    return pdu;
}