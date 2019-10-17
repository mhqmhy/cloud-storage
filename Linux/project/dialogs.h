#ifndef DIALOGS_H
#define DIALOGS_H
#include "allheaders.h"
class ErrorDialog:public QDialog
{
    Q_OBJECT
public:
    ErrorDialog();
    void showError(QString error);
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

class DeleteFileDialog:public QDialog
{
    Q_OBJECT
public:
    QString filename;
    DeleteFileDialog(QString);
    QPushButton * sureBtn;
    QPushButton * cancelBtn;
public slots:
    void deleteFile();
};



#endif // DIALOGS_H
