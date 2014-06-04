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

//Table
#include <QTableWidgetItem>
#include <QClipboard>
#include <QShortcut>


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
    connect(this,SIGNAL(getfileTotal(QString)),fileTotal,SLOT(getfileTotal(QString)));        //request from main thread
    connect(fileTotal,SIGNAL(finished(int)),updater,SLOT(getfileTotal(int)));   //transfer total from getfiletotal object to worker object
    connect(updater,SIGNAL(getfileTotal(QString)),fileTotal,SLOT(getfileTotal(QString)));     //request from updater
    connect(updater,SIGNAL(displayFileTotal(int)),this,SLOT(displayFileTotal(int)));

    connect(fileTotal,SIGNAL(finished(int)),this,SLOT(enableButton()));

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
    emit getfileTotal(dirSelect);
    ui->pushButton->setEnabled(false);



    //TABLE FUNZ
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+C"), this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(on_actionCopy_triggered()));
//    ui->tableWidget->setColumnCount(3);
//    ui->tableWidget->setRowCount(100);

//    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "File" << "Hash" << "Check");
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
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
    if(format)
    emit userSelect("save");
    else
        emit userSelect("saveOld");
}

void MainWindow::on_checkButton_clicked()
{
    ui->textBrowser->clear();
    qDebug() << "check clicked";
    ui->statusBar->showMessage("Checking...",0);
    if(format)
    emit userSelect("check");
    else
        emit userSelect("checkOld");
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
                       tr("<h2>PenguHash v1.1.2</h2>"
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


    ui->tableWidget->setRowCount(numfiles);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "File" << "Hash");


    QStringList rows = text.split('\n');

    for(int i=0; i<numfiles; i++){
        QStringList columns = rows[i].split('\t');
        int troll = 1;
        for(int j=0; j<2; j++){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(columns[troll]));
            troll--;
        }
    }
    //ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

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

    numfiles = updater->numfiles;    //grab number of files from sentry file

    ui->tableWidget->setRowCount(numfiles);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "File" << "Hash" << "Check");



    QStringList rows = updater->checkoutput.split('\n');
    qDebug() << rows;

    if(updater->checkoutput != "")
    for(int i=0; i<numfiles; i++){
        QStringList columns = rows[i].split('\t');
        for(int j=0; j<3; j++){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(columns[j]));
        }
    }
    //ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    updater->checkoutput.clear();


    //emit hidebar();
}



//Menu Actions
void MainWindow::on_actionSet_Directory_triggered()
{
    ui->pushButton->setEnabled(false);
    dirSelect = QFileDialog::getExistingDirectory(this);
    emit selectDir(dirSelect);
    emit getfileTotal(dirSelect);
    qDebug() << dirSelect << endl;
}

void MainWindow::displayFileTotal(int total)
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Files: " + QString::number(total),1000);
    numfiles = total;
}

void MainWindow::enableButton(){
    ui->pushButton->setEnabled(true);
}


void MainWindow::on_actionText_triggered()
{
    ui->actionBinary->setChecked(false);
    format = false;

}

void MainWindow::on_actionBinary_triggered()
{
    ui->actionText->setChecked(false);
    format = true;
}

void MainWindow::on_actionCopy_triggered()
{
    QString str;
    QString s;
    QTextStream ss(&s);

    QList<QTableWidgetSelectionRange> ranges = ui->tableWidget->selectedRanges();

    if(ranges.isEmpty())
        return;

    QTableWidgetSelectionRange range =  ui->tableWidget->selectedRanges().first();
    for(int i=0; i<range.rowCount(); i++){
        if(i>0)
            str += '\n';
        for(int j=0; j<range.columnCount();j++){
            if(j>0)
                str+= "\t";
            if(j==1 && range.columnCount() == 3){
                ss << left << qSetFieldWidth(35) << ui->tableWidget->item(range.topRow()+i,range.leftColumn()+j)->text();
                str+=ui->tableWidget->item(range.topRow()+i,range.leftColumn()+j)->text();
            }
            else{
            ss << left << qSetFieldWidth(55) << ui->tableWidget->item(range.topRow()+i,range.leftColumn()+j)->text() << qSetFieldWidth(0);
            str+=ui->tableWidget->item(range.topRow()+i,range.leftColumn()+j)->text();}
        }
        ss << endl;
    }
    QApplication::clipboard()->setText(s);
   // qDebug() << str;
    //qDebug() << s;

}
