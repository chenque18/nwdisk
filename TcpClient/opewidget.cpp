 #include "opewidget.h"

OpeWidget::OpeWidget(QWidget *parent)
    : QWidget{parent}
{
    m_listWidget=new QListWidget;
    m_listWidget->addItem("好友");
    m_listWidget->addItem("图书");

    m_pfriend=new Friend;
    m_pbook=new Book;

    m_pSW=new QStackedWidget(this);
    m_pSW->addWidget(m_pfriend);
    m_pSW->addWidget(m_pbook);

    QHBoxLayout *pMain = new QHBoxLayout;
    pMain->addWidget(m_listWidget);
    pMain->addWidget(m_pSW);

    setLayout(pMain);
    connect(m_listWidget,SIGNAL(currentRowChanged(int)),m_pSW,SLOT(setCurrentIndex(int)));
}

OpeWidget &OpeWidget::getInstance()
{
    static OpeWidget instance;
    return instance;
}

Friend *OpeWidget::getFriend()
{
    return m_pfriend;
}
