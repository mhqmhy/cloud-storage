#ifndef TREEVIEW_H
#define TREEVIEW_H
#include <QTreeView>
#include <QFileSystemModel>
class TreeView :QTreeView
{
     Q_OBJECT
public:
    TreeView();
    void showWin();

private:
    QFileSystemModel *model;
public slots:
    void printCurrentItem();
    void slotCustomContextMenu(const QPoint &point);
    void test();
};

#endif // TREEVIEW_H
