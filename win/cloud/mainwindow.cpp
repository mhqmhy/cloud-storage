#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QAction>
#include <QToolBar>
#include <QHBoxLayout>
#include <QTreeView>
#include <QDir>
#include <QFileSystemModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFileSystemModel m1;
    m1.setRootPath(QDir::currentPath());
    ui->t1->setModel(&m1);
    ui->t1->setRootIndex(m1.index(QDir::currentPath()));
    QMenu *fileMenu=ui->menubar->addMenu(tr("文件"));
    QAction *action_download=fileMenu->addAction(QIcon("./open.png"),tr("下载文件"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

