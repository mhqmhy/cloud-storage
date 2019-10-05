#include "TreeView.h"
#include <QModelIndex>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QThread>

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
        //upload
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
