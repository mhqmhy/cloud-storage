#include "dialogs.h"

ErrorDialog::ErrorDialog()
{
    this->resize(300,100);
}
void ErrorDialog::showError(QString error)
{
    QLabel *errorLabel=new QLabel(error);
    QVBoxLayout *vboxv=new QVBoxLayout();
    vboxv->addWidget(errorLabel);
    this->setLayout(vboxv);
    this->show();
}


IPDialog :: IPDialog():QDialog()
{
    this->setWindowIcon(QIcon(":/icon1.ico"));
    this->setGeometry(900,500,300,120);
    this->setMinimumSize(220,140);
    QHBoxLayout * hbox=new QHBoxLayout();
    QVBoxLayout * vbox=new QVBoxLayout();
    sureBtn=new QPushButton(tr("确定"),this);
    sureBtn->setMinimumSize(100,40);
    cancelBtn=new QPushButton(tr("关闭"),this);
    cancelBtn->setMinimumSize(100,40);
    hbox->addWidget(sureBtn);
    hbox->addWidget(cancelBtn);
    ipLine=new QLineEdit(this);
    ipLine->setMinimumSize(210,60);
    ipLine->setFont(QFont("Consolas" , 14 ,  QFont::Bold));
    vbox->addWidget(ipLine);
    vbox->addLayout(hbox);
    this->setLayout(vbox);
    connect(sureBtn,SIGNAL(clicked()),this,SLOT(getIPAddr()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(closeDialog()));
}
void IPDialog :: closeDialog()
{
    this->close();
}
void IPDialog :: getIPAddr()
{
   QString addr=this->ipLine->text();
   qDebug()<<tr("ip")<<addr<<endl;
}


DeleteFileDialog::DeleteFileDialog(QString file)
{
    filename=file;
    sureBtn=new QPushButton(tr("sure"));
    cancelBtn=new QPushButton(tr("cancel"));
    QLabel *text=new QLabel();
    text->setText("Do you want to delete "+file+" ?");
    QHBoxLayout *hbox=new QHBoxLayout();
    hbox->addWidget(sureBtn);
    hbox->addWidget(cancelBtn);
    QWidget *w=new QWidget();
    w->setLayout(hbox);
    QVBoxLayout *vbox=new QVBoxLayout();
    vbox->addWidget(text);
    vbox->addWidget(w);
    this->setLayout(vbox);
    connect(sureBtn,SIGNAL(clicked()),this,SLOT(deleteFile()));
}

void DeleteFileDialog::deleteFile()
{
    qDebug()<<"deleting "<<filename<<"..."<<endl;
    this->close();
}
