#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "dialogs.h"
class TreeView : public QTreeView//记得加public 不然是私有继承
{
    Q_OBJECT
    public:
        TreeView(ProgressDialog *);
        QString currentPath;
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
        QString currentPath;
        ProgressDialog *progressDialog;

        ServerTree(ProgressDialog *);

    public slots:
        void addItems();
        void popMenu(const QPoint& point);
        void deleteFile();
        void downloadFile();
        void renameFile();

};
#endif // TREEVIEW_H
