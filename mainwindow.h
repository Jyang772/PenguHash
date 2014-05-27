#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QThread>
#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    //Multi v2
    void saveData();
    void checkData();


    ~MainWindow();

public slots:

    void getCheckSum();
    void checkCompleted();
    void saveCompleted();
    void scanCompleted();




private slots:

    void on_saveButton_clicked();
    void on_checkButton_clicked();
    void on_pushButton_clicked();
    void on_actionAbout_triggered();


    void on_actionSet_Directory_triggered();

protected:
    void closeEvent(QCloseEvent *);
signals:
    void getHash();
    void getCheck();
    void save();
    void sendTest();

    //Multi v2
    void scanFinished();
    void saveFinished();
    void checkFinished();

    void checkTest();

private:
    Ui::MainWindow *ui;
    QByteArray sig;
    QString text;

    QThread *pthread = new QThread(this);
    GUIUpdater *updater = new GUIUpdater();

    QString dirSelect; //User selected directory
};

#endif // MAINWINDOW_H
