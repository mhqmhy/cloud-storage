#ifndef LOGIN_H
#define LOGIN_H

#include "mainwindow.h"
#include "dialogs.h"
//

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
