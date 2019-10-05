#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QTreeView>
#include <QDir>
#include <QFileSystemModel>
#include <QMovie>
#include <QtMultimedia/QSound>
#include <QDesktopServices>
#include <QUrl>
#include "TreeView.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TreeView *tree=new TreeView();
    this->setCentralWidget(tree);
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
    QMenu *menuSetting = ui->menubar->addMenu("帮助");
    QAction *a6=new QAction(tr("更改根目录"));
    menuSetting->addAction(a6);
    QAction *a7=new QAction(tr("产品介绍"));
    menuSetting->addAction(a7);
    QMenu *menuIns = ui->menubar->addMenu("帮助");
    QAction *a8=new QAction(tr("了解我们"));
    menuIns->addAction(a8);
    QAction *a9=new QAction(tr("产品介绍"));
    menuIns->addAction(a9);
    connect(a9, SIGNAL(triggered()), this, SLOT(openGitHub()));
}
void MainWindow :: openGitHub()
{

    QString URL = "https://github.com/SheepHuan/cloud-storage";
    QDesktopServices::openUrl(QUrl(URL.toLatin1()));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void PlayMovie :: getFile(QString file)
{
    this->file=file;
}
void PlayMovie :: run()
{//播放视频

}
void PlaySound :: getFile(QString file)
{
    this->file=file;
}
void PlaySound :: run()
{//播放音乐 WAV格式


}
