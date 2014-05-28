#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

#include <QTextEdit>
#include <QMessageBox>
#include <QProgressDialog>

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




    connect(this,SIGNAL(saveFinished()),this,SLOT(saveCompleted()));
    connect(this,SIGNAL(scanFinished()),this,SLOT(scanCompleted()));
    connect(this,SIGNAL(checkFinished()),this,SLOT(checkCompleted()));

    /*
     * updater->moveToThread(pthread);
    connect(this, SIGNAL(sendTest()),updater,SLOT(doTest()));
    connect(updater,SIGNAL(test()),this,SLOT(test()));
    //User selects option
    connect(this,SIGNAL(getHash()),updater,SLOT(doWork()));
    connect(this,SIGNAL(getCheck()),updater,SLOT(check()));
    connect(this,SIGNAL(save()),updater,SLOT(save()));

    //End of Function
    connect(updater,SIGNAL(Finished()),this,SLOT(getCheckSum()));
    connect(updater,SIGNAL(finishedCheck()),this,SLOT(checkCompleted()));
    connect(updater,SIGNAL(finishedSave()),this,SLOT(saveCompleted()));

    //Clean up thread
    connect(updater,SIGNAL(close()),pthread,SLOT(quit()));
    connect(pthread, SIGNAL(finished()), updater, SLOT(deleteLater()));
    */
    //pthread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *){
    updater->close();
}

//Button Clicked
void MainWindow::on_saveButton_clicked()
{
    QtConcurrent::run(this,&MainWindow::saveData);
    ui->statusBar->showMessage("Saving...",0);
}

void MainWindow::on_checkButton_clicked()
{
    ui->textBrowser->clear();
    qDebug() << "check clicked";
    ui->statusBar->showMessage("Checking...",0);

   QtConcurrent::run(this,&MainWindow::checkData);

}


void MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage("Scanning...",0);
    QtConcurrent::run(this,&MainWindow::getCheckSum);

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About PenguSniff"),
                       tr("<h2>PenguSniff v1.0.0</h2>"
                          "<p>Copyright &copy; 2014 MicroPenguin"
                          "<p>PenguSniff is a simple file integrity monitor/scanner."));

}


//Button Functions

void MainWindow::saveData(){
    QFile file("sentry.dat");



    QTextStream out(&file);
    file.open(QIODevice::WriteOnly);
    //QDir dir = QDir::currentPath();
    QDir dir = dirSelect;

    out << "Directory: " << dirSelect << endl; //prepend directory from which scan was selected to begin from

    QDirIterator dirIt(dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories);
      while(dirIt.hasNext())
      {
          dirIt.next();
          QFile hashFile(dirIt.filePath());
          if(!hashFile.open(QFile::ReadOnly))
          {
              out << "File Error: '" << hashFile.errorString()
                  << "' for file " << dirIt.fileName() << "\n";
          }
          else
          {
              out << QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex()
                  << " : " << hashFile.fileName()/*dirIt.fileName()*/ << "\n";
          }
          out.flush(); //Force output to show up immediately
      }

      emit saveFinished();
}

void MainWindow::getCheckSum()
{
    qDebug() << "PRESSED" << endl;
    QByteArray result;
    QString hash;
    QTextStream out(&result);

    //QDir dir = QDir::currentPath();
    QDir dir = dirSelect;
    QDirIterator dirIt(dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories);
      while(dirIt.hasNext())
      {
          dirIt.next();
          QFile hashFile(dirIt.filePath());
          if(!hashFile.open(QFile::ReadOnly))
          {
              out << "File Error: '" << hashFile.errorString()
                  << "' for file " << dirIt.fileName() << "\n";
          }
          else
          {
              hash = QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex();
              out << hash << " : " << dirIt.fileName() << "\n";


              qDebug() << "Filename: " << QFileInfo(hashFile).fileName() << endl;
              qDebug() << "Hash: " << hash << endl;
          }
          out.flush(); //Force output to show up immediately
      }

    text = QString(result);
    emit scanFinished();


}

void MainWindow::checkData(){
    qDebug() << "IN CHECK";
    QString buffer;
    QVector<QString> fileBuffer;
    QString match;
    QByteArray result;
    QString test;
    QString hash;
    int placeholder = 0;
    int position = 0;
    //ui->textBrowser->clear();

    QFile sentry("sentry.dat");
       if(sentry.open(QIODevice::ReadOnly))
       {
           QTextStream in(&sentry);
           while(!in.atEnd())
           {
               buffer += in.readLine() + "\n";
           }

           sentry.close();
       }

    QTextStream out(result);


    int parse = 0;
    int parsepos = 0;
    int directory = 0; //find directory

    //FIND DIRECTORY
    directory = buffer.indexOf("Directory:",0);
    parse = buffer.indexOf("\n",directory);
    dirSelect = buffer.mid(11,parse-11);
    qDebug() << "PARSE! " << parse << endl;
    qDebug() << "Directory: " << dirSelect << endl;
    //



    //QDir dir = QDir::currentPath();
    QDir dir = dirSelect;

    QDirIterator dirIt(dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories);
      while(dirIt.hasNext())
      {

          dirIt.next();
          QFile hashFile(dirIt.filePath());
          if(!hashFile.open(QFile::ReadOnly))
          {
              out << "File Error: '" << hashFile.errorString()
                  << "' for file " << dirIt.fileName() << "\n";
          }
          else
          {
              fileBuffer.append(hashFile.fileName()/*QFileInfo(hashFile).fileName()*/);

             placeholder = buffer.indexOf(hashFile.fileName()/*QFileInfo(hashFile).fileName()*/, placeholder);     //parse buffer for filenames and hash
             qDebug() << placeholder << endl;
             position = placeholder - 35;                                                   //MD5 hashes are 32 characters in length
             match = buffer.mid(position, 32 );
             placeholder += hashFile.fileName().length(); //QFileInfo(hashFile).fileName().length();

            hash = QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex();


            if(hash == match){

                    QString s;
                    QTextStream ss(&s);
                    ss << left << qSetFieldWidth(50) << QFileInfo(hashFile).fileName() << "PASS" << qSetFieldWidth(0) << endl;
                    test.append(qPrintable(s));
            }

            else if(QFileInfo(hashFile).fileName() == sentry.fileName())
            {
                    QString s;
                    QTextStream ss(&s);
                    ss << left << qSetFieldWidth(50) << QFileInfo(hashFile).fileName() << "SENTRY" << qSetFieldWidth(0) << endl;
                    test.append(qPrintable(s));
            }

            else{
                    QString s;
                    QTextStream ss(&s);

                ss << left << qSetFieldWidth(50) << hashFile.fileName()/*QFileInfo(hashFile).fileName()*/ << "FAIL" << qSetFieldWidth(0) << endl;
                test.prepend((s));
            }
          }


      }

      qDebug() << buffer << endl;

// This should probably go in a separate function //



    QVector<QString> sentryBuffer;
    QString substring;

    QString s;
    QTextStream ss(&s);



for(int i=0; i<buffer.length(); i++){
        parsepos = buffer.indexOf(":",parse);
        if(parsepos == -1)
            continue;
        parse = buffer.indexOf("\n",parsepos+1);
        qDebug() << "parsepos" << parsepos << endl;
        qDebug() << "parse" << parse << endl;
        substring = buffer.mid(parsepos+2, parse-parsepos-2); //plus two for space. Minus difference
        sentryBuffer.append(substring);
        qDebug() << substring << endl;
}


    qDebug() << "sentryBuffer: " <<  sentryBuffer.toList() << endl;
    qDebug() << "fileNames: " << fileBuffer.toList() << endl;
    qDebug() << buffer << endl;
    qDebug() << sentryBuffer.size() << endl;

    for(int i=0; i<sentryBuffer.size(); i++)
       if(fileBuffer.indexOf(sentryBuffer.at(i)) == -1)
       {
           ss << left << qSetFieldWidth(50) << sentryBuffer.at(i) << "MISSING" << qSetFieldWidth(0) << endl;
           //test.prepend(s);
        }



      ss << left << qSetFieldWidth(50) << dirSelect << "DIRECTORY" << qSetFieldWidth(0) << endl;
      test.prepend(s);

      text= test;
      emit checkFinished();

}

//Completed
void MainWindow::scanCompleted()
{
    qDebug() << "SCAN COMPLETE";
    ui->statusBar->showMessage("Scan Complete.",1000);
    ui->textBrowser->setText(QString(text));

}

void MainWindow::saveCompleted()
{
    ui->statusBar->show();
    ui->statusBar->showMessage("Saved to sentry.dat!", 1000);

}

void MainWindow::checkCompleted(){
    qDebug() << "check completed";
    ui->statusBar->showMessage("Check Completed",1000);
    ui->textBrowser->setText(QString(text));

}



//Menu Actions
void MainWindow::on_actionSet_Directory_triggered()
{
    dirSelect = QFileDialog::getExistingDirectory(this);
    qDebug() << dirSelect << endl;
}
