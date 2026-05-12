#ifndef ONLINE_H
#define ONLINE_H
#include"protocol.h"
#include <QWidget>

namespace Ui {
class Online;
}

class Online : public QWidget
{
    Q_OBJECT

public:
    explicit Online(QWidget *parent = nullptr);
    void showUsr(PDU* pdu);
    ~Online();

private:
    Ui::Online *ui;
};

#endif // ONLINE_H
