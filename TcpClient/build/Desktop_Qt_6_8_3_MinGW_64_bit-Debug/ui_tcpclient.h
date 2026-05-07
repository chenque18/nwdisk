/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *name_lab;
    QLineEdit *name_edit;
    QLabel *pwd_lab;
    QLineEdit *pwd_edit;
    QPushButton *login_btn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *regist_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *logout;

    void setupUi(QWidget *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName("TcpClient");
        TcpClient->resize(373, 324);
        widget = new QWidget(TcpClient);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 10, 333, 300));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        name_lab = new QLabel(widget);
        name_lab->setObjectName("name_lab");
        QFont font;
        font.setPointSize(18);
        name_lab->setFont(font);

        gridLayout->addWidget(name_lab, 0, 0, 1, 1);

        name_edit = new QLineEdit(widget);
        name_edit->setObjectName("name_edit");

        gridLayout->addWidget(name_edit, 0, 1, 1, 1);

        pwd_lab = new QLabel(widget);
        pwd_lab->setObjectName("pwd_lab");
        pwd_lab->setFont(font);

        gridLayout->addWidget(pwd_lab, 1, 0, 1, 1);

        pwd_edit = new QLineEdit(widget);
        pwd_edit->setObjectName("pwd_edit");
        pwd_edit->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(pwd_edit, 1, 1, 1, 1);

        login_btn = new QPushButton(widget);
        login_btn->setObjectName("login_btn");
        login_btn->setFont(font);

        gridLayout->addWidget(login_btn, 2, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        regist_btn = new QPushButton(widget);
        regist_btn->setObjectName("regist_btn");
        regist_btn->setFont(font);

        horizontalLayout->addWidget(regist_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        logout = new QPushButton(widget);
        logout->setObjectName("logout");
        logout->setFont(font);

        horizontalLayout->addWidget(logout);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 1, 1, 1, 1);


        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QWidget *TcpClient)
    {
        TcpClient->setWindowTitle(QCoreApplication::translate("TcpClient", "TcpClient", nullptr));
        name_lab->setText(QCoreApplication::translate("TcpClient", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        pwd_lab->setText(QCoreApplication::translate("TcpClient", "\345\257\206   \347\240\201\357\274\232", nullptr));
        login_btn->setText(QCoreApplication::translate("TcpClient", "\347\231\273\345\275\225", nullptr));
        regist_btn->setText(QCoreApplication::translate("TcpClient", "\346\263\250\345\206\214", nullptr));
        logout->setText(QCoreApplication::translate("TcpClient", "\346\263\250\351\224\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
