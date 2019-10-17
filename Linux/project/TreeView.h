#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "dialogs.h"
class TreeView : public QTreeView//记得加public 不然是私有继承
{
    Q_OBJECT
    public:
        TreeView(ProgressDialog *);
        QString currentPath;
//        void showWin();
        QFileSystemModel *model;
        ProgressDialog *progressDialog;
        void loadModel(QString);
    public slots:
        void deleteFile();
        void renameFile();
        void uploadFile();
        void playCurrentItem();
        void slotCustomContextMenu(const QPoint &point);
};
class ServerTree: public QTreeWidget
{
    Q_OBJECT
    public:
        ServerTree(ProgressDialog *);
        ProgressDialog *progressDialog;
    public slots:
        void addOneItem();
        void popMenu(const QPoint& point);
        void deleteFile();
        void downloadFile();
        void renameFile();

};
#endif // TREEVIEW_H
