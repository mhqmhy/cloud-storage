#include "login.h"
#include <vector>
Login::Login():QWidget ()
{
    errorWin=new ErrorDialog();
    this->initUI();
    this->setWindowIcon(QIcon(":/icon1.ico"));
    this->setWindowTitle("Login");
    connect(sureBtn,SIGNAL(clicked()),this,SLOT(checkAccount()));
}
void Login::initUI()
{
    this->setMinimumSize(400,200);
//    this->setMaximumSize(400,200);
    QLabel *labelUsername=new QLabel(tr("UserName"));
    QLabel *labelPasswd=new QLabel(tr("Password"));
    labelUsername->setAlignment(Qt::AlignCenter);
    labelPasswd->setAlignment(Qt::AlignCenter);
    labelUsername->setMinimumSize(120,40);
    labelPasswd->setMinimumSize(120,40);
//    labelUsername->setMaximumSize(120,40);
//    labelPasswd->setMaximumSize(120,40);
    username = new QLineEdit("User");
    passwd = new QLineEdit();
    passwd->setEchoMode(QLineEdit::Password);
    username->setMinimumSize(200,40);
    passwd->setMinimumSize(200,40);
    cancelBtn=new QPushButton(tr("Cancel"));
    sureBtn=new QPushButton(tr("Sure"));
//    sureBtn->setMaximumSize(160,30);
    sureBtn->setMinimumSize(160,30);
//    cancelBtn->setMaximumSize(160,30);
    cancelBtn->setMinimumSize(160,30);
    QHBoxLayout *hbox1=new QHBoxLayout();
    QHBoxLayout *hbox2=new QHBoxLayout();
    QHBoxLayout *hbox3=new QHBoxLayout();
    hbox1->addWidget(labelUsername);
    hbox1->addWidget(username);
    hbox2->addWidget(labelPasswd);
    hbox2->addWidget(passwd);
    hbox3->addWidget(sureBtn);
    hbox3->addWidget(cancelBtn);
    QVBoxLayout *vbox=new QVBoxLayout();
    QWidget *w1=new QWidget();
    w1->setLayout(hbox1);
    QWidget *w2=new QWidget();
    w2->setLayout(hbox2);
    QWidget *w3=new QWidget();
    w3->setLayout(hbox3);
    vbox->addWidget(w1);
    vbox->addWidget(w2);
    vbox->addWidget(w3);
    this->setLayout(vbox);
}


void Login::checkAccount()
{
    QString accountUsername=username->text();
    accountUsername="A";
    QString accountPassWd=passwd->text();
    qDebug()<<accountUsername<<accountPassWd;
    if (accountPassWd.length()!=6){
        QString errorText="password error";
        errorWin->showError(errorText);
    }
    else {
         std::vector<string> a;
           if (!ProcessList(a,accountUsername.toStdString(),accountPassWd.toStdString()))
           {
               qDebug()<<a.size()<<endl;
//               for(vector<string>::iterator iter = a.begin();iter != a.end();iter++)
//               {
//                   std::cout << *iter <<std::endl;
//               }
               for (int i=0;i<a.size();i++)
               {
                  qDebug()<<QString::fromStdString(a[i])<<endl;
               }
           }
           showMainWindow();

    }

}

void Login::showMainWindow()
{
    MainWindow *win=new MainWindow();
    win->show();
    win->username=this->username->text();
    win->passwd=this->passwd->text();
}


