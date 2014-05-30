#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

#include <QTextEdit>
#include <QMessageBox>
#include <QProgressBar>

//File I/O
#include <QFileDialog>

//Threading
#include <thread>
#include <QtConcurrentRun>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setFont(QFont("Monospace",11));
    ui->textBrowser->setLineWrapMode(QTextEdit::NoWrap);

    updater->moveToThread(pthread);
    fileTotal->moveToThread(fthread);

    //User selects directory, or action
    connect(this,SIGNAL(userSelect(QString)),updater,SLOT(action(QString)));
    connect(this,SIGNAL(selectDir(QString)),updater,SLOT(selectDir(QString)));
    connect(this,SIGNAL(selectDir(QString)),fileTotal,SLOT(selectDir(QString)));

    //Returning from Worker Thread
    connect(updater,SIGNAL(Finished(QString)),this,SLOT(action(QString)));

    //Clean up threads
    connect(updater,SIGNAL(close()),pthread,SLOT(quit()));
    connect(pthread, SIGNAL(finished()), updater, SLOT(deleteLater()));
    connect(fileTotal,SIGNAL(close()),fthread,SLOT(quit()));
    connect(fthread,SIGNAL(finished()),fileTotal,SLOT(deleteLater()));

    //Start Thread(s)
    pthread->start();
    fthread->start();

    //Get number of files in directory for progress bar
    //connect(this,SIGNAL(getfileTotal()),updater,SLOT(getfileTotal()));
    connect(this,SIGNAL(getfileTotal()),fileTotal,SLOT(getfileTotal()));        //request from main thread
    connect(fileTotal,SIGNAL(finished(int)),updater,SLOT(getfileTotal(int)));   //transfer total from getfiletotal object to worker object
    connect(updater,SIGNAL(getfileTotal()),fileTotal,SLOT(getfileTotal()));     //request from updater
    connect(updater,SIGNAL(displayFileTotal(int)),this,SLOT(displayFileTotal(int)));

    //Create ProgressBar
    QProgressBar *bar = new QProgressBar(ui->statusBar);
    ui->statusBar->addWidget(bar);
    bar->setRange(0,100);
    bar->setValue(0);
    bar->hide();
    connect(updater,SIGNAL(percentChanged(int)),bar,SLOT(setValue(int)));
    connect(updater,SIGNAL(percentChanged(int)),bar,SLOT(show()));
    connect(this,SIGNAL(hidebar()),bar,SLOT(hide()));

    //fileTotal->getfileTotal();
    emit getfileTotal();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *){
    updater->close();
    fileTotal->close();
}

//Button Clicked
void MainWindow::on_saveButton_clicked()
{
    //QtConcurrent::run(this,&MainWindow::saveData);
    ui->statusBar->showMessage("Saving...",0);
    emit userSelect("save");
}

void MainWindow::on_checkButton_clicked()
{
    ui->textBrowser->clear();
    qDebug() << "check clicked";
    ui->statusBar->showMessage("Checking...",0);
    emit userSelect("check");
   //QtConcurrent::run(this,&MainWindow::checkData);

}

void MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage("Scanning...",0);

    emit userSelect("scan");

    //QtConcurrent::run(this,&MainWindow::getCheckSum);

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About PenguSniff"),
                       tr("<h2>PenguSniff v1.0.0</h2>"
                          "<p>Copyright &copy; 2014 MicroPenguin"
                          "<p>PenguSniff is a simple file integrity monitor/scanner."));

}


//Completed
//Determine which action to take
void MainWindow::action(QString method){
    switch(test(method)){

    case scanFinished:{
        scanCompleted();}
        break;
    case checkFinished:{
        checkCompleted();}
        break;
    case saveFinished:{
        saveCompleted();}
        break;
    case none:
        break;
    }


}

void MainWindow::scanCompleted()
{
    qDebug() << "SCAN COMPLETE";
    ui->statusBar->showMessage("Scan Complete.",1000);
    text = updater->result2;
    ui->textBrowser->setText(QString(text));
    emit hidebar();
}

void MainWindow::saveCompleted()
{
    ui->statusBar->show();
    ui->statusBar->showMessage("Saved to sentry.dat!", 1000);
    emit hidebar();
}

void MainWindow::checkCompleted(){
    qDebug() << "check completed";
    ui->statusBar->showMessage("Check Completed",1000);
    text = updater->result2;
    ui->textBrowser->setText(QString(text));
    emit hidebar();
}



//Menu Actions
void MainWindow::on_actionSet_Directory_triggered()
{
    dirSelect = QFileDialog::getExistingDirectory(this);
    emit selectDir(dirSelect);
    emit getfileTotal();
    qDebug() << dirSelect << endl;
}

void MainWindow::displayFileTotal(int total)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Files: " + QString::number(total),1000);
}
