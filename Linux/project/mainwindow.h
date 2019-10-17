#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include <QDialog>
#include <QThread>
#include <QPushButton>
#include <QLineEdit>
#include "TreeView.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   QString username,passwd;
   void updateServerList();
   ServerTree *serverTree;
   TreeView *localTree;
private:
    Ui::MainWindow *ui;
public slots:
    void updateLocalList();
    void downloadFile()
    {
        qDebug()<<"downloading"<<endl;
    }
    void openGitHub();//默认浏览器定位到github仓库
    void openIntroduce();//默认浏览器定位到产品介绍.md
    void chgServerIp();
    void chgLoaclRootDir();

};
class IPDialog: public QDialog
{
    Q_OBJECT
public:
    QPushButton * sureBtn;
    QPushButton * cancelBtn;
    QLineEdit *ipLine;
    IPDialog();
public slots:
    void closeDialog();
    void getIPAddr();
};

#endif // MAINWINDOW_H
