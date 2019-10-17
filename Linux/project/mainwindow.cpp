#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    pDialog=new ProgressDialog();
    QHBoxLayout *hbLayout = new QHBoxLayout();
    serverTree=new ServerTree(pDialog);
    localTree=new TreeView(pDialog);
    hbLayout->addWidget(localTree);
    hbLayout->addWidget(serverTree);
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
    QToolBar *toolBar_chgDIr = addToolBar(tr("File"));
    QAction *a6=new QAction(tr("更改根目录"));
    toolBar_chgDIr->addAction(a6);
    menuSetting->addAction(a6);
    connect(a6,SIGNAL(triggered()),this,SLOT(updateLocalList()));
    QAction *a7=new QAction(tr("设置服务器地址"));//更改服务器地址
    menuSetting->addAction(a7);
    connect(a7, SIGNAL(triggered()), this, SLOT(chgServerIp()));
    QToolBar *toolBar_noUs = addToolBar(tr("File"));
    QMenu *menuIns = ui->menubar->addMenu("帮助");
    QAction *a8=new QAction(tr("了解我们"));
    toolBar_noUs->addAction(a8);
    menuIns->addAction(a8);
    connect(a8, SIGNAL(triggered()), this, SLOT(openGitHub()));
    QAction *a9=new QAction(tr("产品介绍"));
    menuIns->addAction(a9);
    connect(a9, SIGNAL(triggered()), this, SLOT(openIntroduce()));


    QToolBar *toolBar_progress = addToolBar(tr("File"));
    QAction *a10=new QAction(tr("ProgressBar"));
    toolBar_progress->addAction(a10);
    connect(a10,SIGNAL(triggered()),this,SLOT(showProgressBar()));
}
void  MainWindow :: chgServerIp()
{
    IPDialog *dialog =new IPDialog();
    dialog->show();

}
void MainWindow :: chgLoaclRootDir()
{


}

void MainWindow::showProgressBar()
{
    pDialog->show();
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

}

void MainWindow::updateLocalList()
{
    qDebug()<<"ok"<<endl;
    QString srcDirPath = QFileDialog::getExistingDirectory(
    this, "choose src Directory",  "/");
    if (srcDirPath.isEmpty())
    {
        return;
    }
    else
    {
        qDebug() << "srcDirPath=" << srcDirPath;
        this->localTree->model->setRootPath(srcDirPath);
        this->localTree->setModel(this->localTree->model);
        this->localTree->setRootIndex(this->localTree->model->index(srcDirPath));
    }
}









