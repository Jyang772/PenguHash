#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
//#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getCheckSum();
    void formatting();
    bool savetoFile = false;


private slots:


    void on_saveButton_clicked();

    void on_checkButton_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray sig;
    QString buffer;


};

#endif // MAINWINDOW_H
