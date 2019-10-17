#include "TreeView.h"

TreeView::TreeView(ProgressDialog *p) :QTreeView()
{
    progressDialog=p;
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    currentPath=QDir::currentPath();
    connect(this,SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(slotCustomContextMenu(const QPoint &)));
    model=new QFileSystemModel();
    loadModel(QDir::currentPath());
    this->setWindowTitle(tr("本地目录"));
    connect(this,SIGNAL(doubleClicked ( const QModelIndex)),this,SLOT(playCurrentItem()));


}

void TreeView::loadModel(QString path)
{
    currentPath=path;
    this->model->setRootPath(path);
    this->setModel(this->model);
    this->setRootIndex(this->model->index(path));
}
void TreeView::slotCustomContextMenu(const QPoint &point)
{
        QMenu *menu = new QMenu(this);
        QAction *a1=new QAction(tr("Upload"));
        connect(a1,SIGNAL(triggered()),this,SLOT(uploadFile()));
        menu->addAction(a1);
        QAction *a3=new QAction(tr("Rename"));
        menu->addAction(a3);
        connect(a3,SIGNAL(triggered()),this,SLOT(renameFile()));
        QAction *a4=new QAction(tr("Delete"));
        menu->addAction(a4);
        connect(a4,SIGNAL(triggered()),this,SLOT(deleteFile()));
        menu->exec(this->mapToGlobal(point));

}

void TreeView::deleteFile()
{

    QModelIndex selected = this->currentIndex(); //选中的行
    selected = selected.sibling(selected.row(),0); //0 就是第一列元素，1就是第二列元素，依此类推
    QString file(this->model->itemData(selected).values()[0].toString()); //由你自己每一列的QVariant绑定的值，决定获取数据的方式
    qDebug()<<tr("file")<<file<<endl;
    DeleteFileDialog* deleteDialog =new DeleteFileDialog(file);
    deleteDialog->show();



    loadModel(currentPath);
}

void TreeView::renameFile()
{
    QModelIndex selected = this->currentIndex(); //选中的行
    selected = selected.sibling(selected.row(),0); //0 就是第一列元素，1就是第二列元素，依此类推
    QString file(this->model->itemData(selected).values()[0].toString()); //由你自己每一列的QVariant绑定的值，决定获取数据的方式
    qDebug()<<tr("rename ")<<file<<endl;



    loadModel(currentPath);
}

void TreeView::uploadFile()
{
    QModelIndex selected = this->currentIndex(); //选中的行
    selected = selected.sibling(selected.row(),0); //0 就是第一列元素，1就是第二列元素，依此类推
    QString file(this->model->itemData(selected).values()[0].toString()); //由你自己每一列的QVariant绑定的值，决定获取数据的方式
    qDebug()<<tr("uploading ")<<file<<endl;
    if (progressDialog->isHidden())
        progressDialog->show();
    progressDialog->setProgressBar(file);
    loadModel(currentPath);
}
void TreeView::playCurrentItem()
{
    qDebug()<<tr("OK")<<endl;
    QModelIndex index=this->currentIndex();
    qDebug()<<tr("index: ")<<index<<endl;
    QString filename=this->model->data(index).toString();
    qDebug()<<tr("filename: ")<<filename<<tr("filepath: ")<<endl;

}


ServerTree::ServerTree(ProgressDialog *p) :QTreeWidget()
{
    progressDialog=p;
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
    QAction *downloadItem=new QAction(tr("Download"));
    QAction *reNameItem=new QAction(tr("Rename"));
    QAction *deleteItem=new QAction(tr("Delete"));
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
    QTreeWidgetItem* t=this->currentItem();
    QString file=t->text(0);
    qDebug()<<tr("file")<<file<<endl;
    DeleteFileDialog* deleteDialog =new DeleteFileDialog(file);

    deleteDialog->show();
}

void ServerTree::downloadFile()//downlaod file
{
    QTreeWidgetItem* t=this->currentItem();
    QString file=t->text(0);
    qDebug()<<tr("downloading ")<<file<<endl;
    if (progressDialog->isHidden())
        progressDialog->show();
    progressDialog->setProgressBar(file);
}

void ServerTree::renameFile()
{
    QTreeWidgetItem* t=this->currentItem();
    QString file=t->text(0);
    qDebug()<<tr("rename ")<<file<<endl;
}
void ServerTree::addOneItem()
{


}
