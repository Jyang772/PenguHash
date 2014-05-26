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
    ~MainWindow();
public slots:

    void getCheckSum();
    void checkCompleted();
    void saveCompleted();

private slots:

    void on_saveButton_clicked();
    void on_checkButton_clicked();
    void on_pushButton_clicked();
    void on_actionAbout_triggered();


protected:
    void closeEvent(QCloseEvent *);
signals:
    void getHash();
    void getCheck();
    void save();

private:
    Ui::MainWindow *ui;
    QByteArray sig;
    QString buffer;

    QThread *pthread = new QThread(this);
    GUIUpdater *updater = new GUIUpdater();
};

#endif // MAINWINDOW_H
