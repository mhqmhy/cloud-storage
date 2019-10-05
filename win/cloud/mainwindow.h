#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include <QDialog>
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void showChildDialog()
    {
        QDialog *dialog=new QDialog();
        dialog->show();
    }
    void downloadFile()
    {
        qDebug()<<"downloading"<<endl;
    }
public slots:
    void openGitHub();

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
