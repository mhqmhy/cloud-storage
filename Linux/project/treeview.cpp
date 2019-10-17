#include "TreeView.h"
#include <QModelIndex>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QThread>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
TreeView::TreeView() :QTreeView()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(slotCustomContextMenu(const QPoint &)));
    model=new QFileSystemModel();
    model->setRootPath(QDir::currentPath());
    this->setModel(model);
    this->setRootIndex(model->index(QDir::currentPath()));
    this->setWindowTitle(tr("本地目录"));
    connect(this,SIGNAL(doubleClicked ( const QModelIndex)),this,SLOT(playCurrentItem()));
    //upload


}
void TreeView::showWin()
{
    this->show();
}
void TreeView::playCurrentItem()
{
    qDebug()<<tr("OK")<<endl;
    QModelIndex index=this->currentIndex();
    qDebug()<<tr("index: ")<<index<<endl;
    QString filename=this->model->data(index).toString();
    qDebug()<<tr("filename: ")<<filename<<tr("filepath: ")<<endl;
//    qDebug("%s",qUtf8Printable("你好"));
}
void TreeView::slotCustomContextMenu(const QPoint &point)
{
        QMenu *menu = new QMenu(this);
        QAction *a1=new QAction(tr("上传"));
        menu->addAction(a1);
        QAction *a2=new QAction(tr("移动"));
        menu->addAction(a2);
        QAction *a3=new QAction(tr("复制"));
        menu->addAction(a3);
        QAction *a4=new QAction(tr("删除"));
        menu->addAction(a4);
        menu->exec(this->mapToGlobal(point));

}

ServerTree::ServerTree() :QTreeWidget()
{
    this->setColumnCount(2);  //设置列
    this->setHeaderLabels({tr("Name"),tr("type")});    //设置表头
    QList<QTreeWidgetItem *> items;
    QTreeWidgetItem *first = new QTreeWidgetItem;
    first->setText(0,"first");
    first->setText(1,"txt");
    items.append(first);

     QTreeWidgetItem *second = new QTreeWidgetItem;   //添加第二个父节点
    second->setText(0, tr("second"));
    second->setText(1,"txt");
    items.append(second);
    this->insertTopLevelItems(0, items);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint&)), this,SLOT(popMenu(const QPoint&)));//右键菜单事件
}
void ServerTree::popMenu(const QPoint &point)
{
    QAction *downloadItem=new QAction(tr("下载"));
    QAction *reNameItem=new QAction(tr("重命名"));
    QAction *deleteItem=new QAction(tr("删除"));
    connect(deleteItem, SIGNAL(triggered()), this, SLOT(deleteFile()));
    connect(reNameItem,SIGNAL(triggered()),this,SLOT(renameFile()));
    connect(downloadItem,SIGNAL(triggered()),this,SLOT(downloadFile()));
    QMenu menu(this);
    menu.addAction(downloadItem);
    menu.addAction(reNameItem);
    menu.addAction(deleteItem);
    menu.exec(this->mapToGlobal(point));

}

void ServerTree::deleteFile()
{

}

void ServerTree::downloadFile()//downlaod file
{

}

void ServerTree::renameFile()
{

}
void ServerTree::addOneItem()
{


}
