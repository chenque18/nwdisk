#ifndef OPEWIDGET_H
#define OPEWIDGET_H

#include <QWidget>
#include<QListWidget>
#include <QStackedWidget>
#include "book.h"
#include "friend.h"
class OpeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpeWidget(QWidget *parent = nullptr);
    static OpeWidget& getInstance();
    Friend*getFriend();
private:
    QListWidget *m_listWidget;
    Friend *m_pfriend;
    Book *m_pbook;
    QStackedWidget *m_pSW;
signals:
};

#endif // OPEWIDGET_H
