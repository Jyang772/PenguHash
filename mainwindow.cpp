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

    updater->moveToThread(thread);
    connect(updater,SIGNAL(req()), this, SLOT(getCheckSum()));
    connect(thread, SIGNAL(destroyed()), updater, SLOT(deleteLater()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::getCheckSum()
{

    QByteArray result;
    QString hash;
    QTextStream out(&result);

    QDir dir = QDir::currentPath();
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

      ui->textBrowser->setText(QString(result));
}


void MainWindow::on_saveButton_clicked()
{


    QFile file("sentry.dat");



    QTextStream out(&file);
    file.open(QIODevice::WriteOnly);
    QDir dir = QDir::currentPath();
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


    ui->statusBar->show();
    ui->statusBar->showMessage("Saved to sentry.dat!", 1000);

}

void MainWindow::on_checkButton_clicked()
{

    QString buffer;
    QVector<QString> fileBuffer;
    QString match;
    QByteArray result;
    QString test;
    QString hash;
    int placeholder = 0;
    int position = 0;

    ui->textBrowser->clear();

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

       //qDebug() << "Buffer: " << buffer << endl;


    QTextStream out(result);

    QDir dir = QDir::currentPath();
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
             position = placeholder - 35;                                                   //MD5 hashes are 32 characters in length
             match = buffer.mid(position, 32 );
             placeholder += hashFile.fileName().length(); //QFileInfo(hashFile).fileName().length();

            hash = QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex();


            if(hash == match){

                    QString s;
                    QTextStream ss(&s);
                    ss << left << qSetFieldWidth(50) << QFileInfo(hashFile).fileName() << "PASS" << qSetFieldWidth(0) << endl;
                    test.append(qPrintable(s));
;
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

    int parse = 0;
    int parsepos = 0;
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
        substring = buffer.mid(parsepos+2, parse-parsepos-2); //plus two for space
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

      test.prepend(s);

      ui->textBrowser->setText(test);


}

void MainWindow::on_pushButton_clicked()
{
    updater->getHash();
    //getCheckSum();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About PenguSniff"),
                       tr("<h2>PenguSniff v1.0.0</h2>"
                          "<p>Copyright &copy; 2014 MicroPenguin"
                          "<p>PenguSniff is a simple file integrity monitor/scanner."));

}

