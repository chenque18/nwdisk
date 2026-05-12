#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>
#include"protocol.h"
class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    QString getname();

public slots:
    void receiveMsg();
    void clientOFFline();
private:
    QString m_strName;
signals:
    void OFFline(MyTcpSocket*mysocket);
};

#endif // MYTCPSOCKET_H
