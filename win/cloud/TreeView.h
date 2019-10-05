#ifndef TREEVIEW_H
#define TREEVIEW_H
#include <QTreeView>
#include <QFileSystemModel>
 class TreeView : public QTreeView//记得加public 不然是私有继承
{
     Q_OBJECT
public:
    TreeView();
    void showWin();
    QFileSystemModel *model;

public slots:

    void printCurrentItem();
    void slotCustomContextMenu(const QPoint &point);
    void test();
};

#endif // TREEVIEW_H
