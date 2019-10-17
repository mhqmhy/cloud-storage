#ifndef LOGIN_H
#define LOGIN_H
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QDialog>
#include "mainwindow.h"
//
class ErrorDialog:public QDialog
{
    Q_OBJECT
public:
    ErrorDialog();
    void showError(QString error);

};
class Login:public QWidget
{
    Q_OBJECT
public:
    QLineEdit *passwd;
    QLineEdit *username;
    QPushButton *sureBtn;
    QPushButton *cancelBtn;
    ErrorDialog *errorWin;
    Login();
    void initUI();
    void showMainWindow();


public slots:
    void checkAccount();


};

#endif // LOGIN_H
