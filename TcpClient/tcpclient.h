#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include<QFile>
#include<QTcpSocket>
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
public slots:
    //捕获连接信号槽函数
    void showConnect();
    void receivemsg();
private slots:
    //void on_send_pb_clicked();

    void on_login_btn_clicked();

    void on_regist_btn_clicked();

    void on_logout_clicked();

private:
    Ui::TcpClient *ui;
    //存放ip和port
    QString m_strIP;
    quint16 m_usPort;
    //需要连接服务器进行数据交互
    QTcpSocket m_tcpSocket;
};
#endif // TCPCLIENT_H
