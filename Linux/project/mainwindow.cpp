#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QDir>
#include <QFileSystemModel>
#include <QMovie>
#include <QtMultimedia/QSound>
#include <QDesktopServices>
#include <QUrl>
#include <QPushButton>
#include <QTreeWidget>
#include <QLineEdit>
#include <QDebug>
#include "TreeView.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon1.ico"));
    this->setWindowTitle("摆渡云 众里寻他千百度");
    QWidget * wid=new QWidget();
    this->setCentralWidget(wid);

    QHBoxLayout *hbLayout = new QHBoxLayout();
    ServerTree *t=new ServerTree();
    TreeView *tree=new TreeView();
    hbLayout->addWidget(tree);
    hbLayout->addWidget(t);
    wid->setLayout(hbLayout);



//设置菜单栏
    QMenu *menu = ui->menubar->addMenu("文件");
    QAction *a1=new QAction(tr("上传"));
    menu->addAction(a1);
    QAction *a2=new QAction(tr("移动"));
    menu->addAction(a2);
    QAction *a3=new QAction(tr("复制"));
    menu->addAction(a3);
    QAction *a4=new QAction(tr("删除"));
    menu->addAction(a4);
    QAction *a5=new QAction(tr("删除"));
    menu->addAction(a5);
    QMenu *menuSetting = ui->menubar->addMenu("设置");
    QAction *a6=new QAction(tr("更改根目录"));
    menuSetting->addAction(a6);
    QAction *a7=new QAction(tr("设置服务器地址"));//更改服务器地址
    menuSetting->addAction(a7);
    connect(a7, SIGNAL(triggered()), this, SLOT(chgServerIp()));
    QMenu *menuIns = ui->menubar->addMenu("帮助");
    QAction *a8=new QAction(tr("了解我们"));
    menuIns->addAction(a8);
    connect(a8, SIGNAL(triggered()), this, SLOT(openGitHub()));
    QAction *a9=new QAction(tr("产品介绍"));
    menuIns->addAction(a9);
    connect(a8, SIGNAL(triggered()), this, SLOT(openIntroduce()));
}
void  MainWindow :: chgServerIp()
{
    IPDialog *dialog =new IPDialog();
    dialog->show();

}
void MainWindow :: chgLoaclRootDir()
{


}
void MainWindow :: openIntroduce()
{

    QString URL = "https://github.com/SheepHuan/cloud-storage/blob/master/%E4%BA%A7%E5%93%81%E4%BB%8B%E7%BB%8D.md";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));

}
void MainWindow:: openGitHub()
{
    QString URL = "https://github.com/SheepHuan/cloud-storage";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateServerList()
{
    //
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




