#include "login.h"

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

    QLabel *labelUsername=new QLabel(tr("UserName"));
    QLabel *labelPasswd=new QLabel(tr("Password"));
    username = new QLineEdit("User");
    passwd = new QLineEdit();
    cancelBtn=new QPushButton(tr("Cancel"));
    sureBtn=new QPushButton(tr("Sure"));
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
    QString accountPassWd=passwd->text();
    qDebug()<<accountUsername<<accountPassWd;
    if (accountPassWd.length()!=6){
        QString errorText="password error";
        errorWin->showError(errorText);
    }
    else {
        showMainWindow();
        this->close();
    }

}

void Login::showMainWindow()
{
    MainWindow *win=new MainWindow();
    win->show();
    win->username=this->username->text();
    win->passwd=this->passwd->text();
}


