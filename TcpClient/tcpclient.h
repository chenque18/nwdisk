#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>

#include<QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class TcpClient;
}
QT_END_NAMESPACE

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient() override;
    //初始化加载配置文件
    void loadConfig();

private:
    Ui::TcpClient *ui;
    //存放ip和port
    QString m_strIP;
    quint16 m_usPort;
};
#endif // TCPCLIENT_H
