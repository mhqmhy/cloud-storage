#ifndef TREEVIEW_H
#define TREEVIEW_H
#include <QTreeView>
#include <QTreeWidget>
#include <QFileSystemModel>
class TreeView : public QTreeView//记得加public 不然是私有继承
{
    Q_OBJECT
    public:
        TreeView();
        void showWin();
        QFileSystemModel *model;
    public slots:
        void playCurrentItem();
        void slotCustomContextMenu(const QPoint &point);
};
class ServerTree: public QTreeWidget
{
    Q_OBJECT
    public:
        ServerTree();
    public slots:
        void addOneItem();
        void popMenu(const QPoint& point);
        void deleteFile();
        void downloadFile();
        void renameFile();

};
#endif // TREEVIEW_H
