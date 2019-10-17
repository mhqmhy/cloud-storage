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
#include "login.h"
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
//    MainWindow * w=new MainWindow();
//    w->show();
     Login *login=new Login();
     login->show();


  return a.exec();
}
