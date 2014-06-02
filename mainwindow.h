#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QThread>
#include <QStandardItemModel>

#include "worker.h"
#include "getfiletotal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);



    enum Code{
        saveFinished,
        checkFinished,
        scanFinished,
        none
    };

    Code test(QString method){
        if(method == "scanFinished")
            return scanFinished;
         if(method == "checkFinished")
            return checkFinished;
        if(method == "saveFinished")
            return saveFinished;
        return none;
    }




    //Multi v2
    void saveData();
    void checkData();


    ~MainWindow();

public slots:

    void action(QString);

    void checkCompleted();
    void saveCompleted();
    void scanCompleted();


private slots:

    void on_saveButton_clicked();
    void on_checkButton_clicked();
    void on_pushButton_clicked();
    void on_actionAbout_triggered();


    void on_actionSet_Directory_triggered();
    void displayFileTotal(int);
    void enableButton();


    void on_actionText_triggered();

    void on_actionBinary_triggered();

    void on_actionCopy_triggered();

protected:
    void closeEvent(QCloseEvent *);
signals:
    void getHash();
    void getCheck();
    void save();
    void sendTest();



    void checkTest();

    //Multi v4
    void userSelect(QString);
    void selectDir(QString);
    void hidebar();
    void getfileTotal();

private:
    Ui::MainWindow *ui;
    QByteArray sig;
    QString text;
    bool format = false;

    QThread *pthread = new QThread(this);
    QThread *fthread = new QThread(this);
    GetFileTotal *fileTotal = new GetFileTotal();
    GUIUpdater *updater = new GUIUpdater();

    QString dirSelect; //User selected directory

    int numfiles;

};

#endif // MAINWINDOW_H
