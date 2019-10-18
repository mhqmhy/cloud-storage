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
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(closeDialog()));
}

void DeleteFileDialog::deleteFile()
{
    qDebug()<<"deleting "<<filename<<"..."<<endl;
    this->close();
}

void DeleteFileDialog::closeDialog()
{
    this->close();
}
class MyThread:public QThread
{
public:
    MyThread();
   QProgressBar *pBar;
   QLabel *status;
protected:
   virtual  void run();
};
MyThread::MyThread()
{
    //empty;
}

void MyThread::run()
{

    status->setText("Waitting");
    for (int i=0;i<=10;i++)
    {
        sleep(1);
        pBar->setValue(i*10);
    }
    status->setText("Finished");

}
ProgressDialog::ProgressDialog()
{
    vbox=new QVBoxLayout();
    this->setLayout(vbox);
    this->resize(400,100);
}

void ProgressDialog::setProgressBar(QString file)
{
    QHBoxLayout *hbox=new QHBoxLayout();
    QLabel *filename=new QLabel();
//    filename->setMaximumSize(100,60);
    filename->setText(file);
    QLabel *status=new QLabel();
    status->setText("Waitting");
    status->setMaximumSize(100,60);
    QProgressBar *pBar=new QProgressBar();
    pBar->resize(200,50);
    pBar->setMaximumSize(1000,80);
    pBar->setOrientation(Qt::Horizontal);  //水平方向
    pBar->setRange(0,100);
    QWidget *w=new QWidget();
    hbox->addWidget(filename);
    hbox->addWidget(pBar);
    hbox->addWidget(status);
    w->setLayout(hbox);
    vbox->addWidget(w);
    showBar(pBar,status);
    status->setText("Finished");
}

void ProgressDialog::showBar(QProgressBar *pBar,QLabel *status)
{
    MyThread *t=new MyThread();
    t->pBar=pBar;
    t->status=status;
    t->start();
}


