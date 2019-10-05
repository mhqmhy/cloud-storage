/**
* 书本:【Qt5开发及实例】
* 功能:实现MVC的模型/视图类
* 文件:main.cpp
* 时间:2015年1月27日12:29:22
* 作者:cutter_point
*/
#include <QApplication>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QCoreApplication>
#include <QFileInfo>
#include <QTextCodec>
#include <QStringList>
#include <QDateTime>
#include <QDebug>
#include <QDirModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QModelIndex>
#include "mainwindow.h"
#include "TreeView.h"

void fileSystem()
{
    QFileSystemModel model;
    model.setRootPath(QDir::currentPath());
    QTreeView tree;
    tree.setModel(&model);
    tree.setRootIndex(model.index(QDir::currentPath()));
    tree.show();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TreeView *t;
    t=new TreeView();

    t->showWin();




  return a.exec();
}
