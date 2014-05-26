#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

#include <QTextEdit>
#include <QMessageBox>
#include <QProgressDialog>
#include <iostream>
#include <thread>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setFont(QFont("Monospace",11));
    ui->textBrowser->setLineWrapMode(QTextEdit::NoWrap);

    updater->moveToThread(pthread);
    connect(this,SIGNAL(getHash()),updater,SLOT(doWork()));
    connect(this,SIGNAL(getCheck()),updater,SLOT(check()));
    connect(this,SIGNAL(save()),updater,SLOT(save()));

    connect(updater,SIGNAL(Finished()),this,SLOT(getCheckSum()));
    connect(updater,SIGNAL(finishedCheck()),this,SLOT(checkCompleted()));
    connect(updater,SIGNAL(finishedSave()),this,SLOT(saveCompleted()));

    connect(updater,SIGNAL(close()),pthread,SLOT(quit()));
    connect(pthread, SIGNAL(finished()), updater, SLOT(deleteLater()));
    pthread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *){
    updater->close();
}

void MainWindow::getCheckSum()
{
    ui->textBrowser->setText(updater->result2);
    ui->statusBar->clearMessage();
    return;

}

void MainWindow::on_saveButton_clicked()
{
    emit save();
    ui->statusBar->showMessage("Saving...",0);
}


void MainWindow::on_checkButton_clicked()
{
    ui->textBrowser->clear();
    qDebug() << "check clicked";
    ui->statusBar->showMessage("Checking...",0);
    emit getCheck();
}

void MainWindow::checkCompleted(){
    qDebug() << "check completed";
    ui->statusBar->showMessage("Check Completed",1000);
    ui->textBrowser->setText(updater->result2);

}
void MainWindow::saveCompleted(){
    ui->statusBar->show();
    ui->statusBar->showMessage("Saved to sentry.dat!", 1000);

}

void MainWindow::on_pushButton_clicked()
{
    //pthread->start();
    emit getHash();

    ui->statusBar->showMessage("Scanning...",0);
    //updater->getpHash();
    //ui->textBrowser->setText(updater->result2);
    //getCheckSum();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About PenguSniff"),
                       tr("<h2>PenguSniff v1.0.0</h2>"
                          "<p>Copyright &copy; 2014 MicroPenguin"
                          "<p>PenguSniff is a simple file integrity monitor/scanner."));

}

