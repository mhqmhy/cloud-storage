#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include <QDialog>
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

};
#endif // MAINWINDOW_H
