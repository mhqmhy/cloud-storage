#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include <QDialog>
#include <QThread>
#include <QPushButton>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
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
class PlaySound: public QThread
{
protected:
    void run();
private:
    QString file;
public:
    void getFile(QString file);
};
class PlayMovie:public QThread
{
protected:
    void run();
private:
    QString file;
public:
    void getFile(QString file);
};
#endif // MAINWINDOW_H
