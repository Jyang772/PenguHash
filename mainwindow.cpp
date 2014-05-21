#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextEdit>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setFont(QFont("Monospace",11));
    ui->textBrowser->setLineWrapMode(QTextEdit::NoWrap);
    getCheckSum();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::getCheckSum()
{

    QByteArray result;
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
              out << QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex()
                  << " : " << dirIt.fileName() << "\n";


              qDebug() << "Filename: " << QFileInfo(hashFile).fileName() << endl;
              qDebug() << "Hash: " << QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex() << endl;
          }
          out.flush(); //Force output to show up immediately
      }

      ui->textBrowser->setText(QString(result));



        savetoFile = false;

}


void MainWindow::on_saveButton_clicked()
{
    savetoFile = true;


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
                  << " : " << dirIt.fileName() << "\n";
          }
          out.flush(); //Force output to show up immediately
      }


    ui->statusBar->show();
    ui->statusBar->showMessage("Saved to sentry.dat!", 1000);

}

void MainWindow::on_checkButton_clicked()
{

    QString buffer;
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
               buffer += in.readLine();
           }

           sentry.close();
       }

       qDebug() << "Buffer: " << buffer << endl;


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

             placeholder = buffer.indexOf(QFileInfo(hashFile).fileName(), placeholder);
             //Check for missing/deleted files
             position = placeholder - 35;
             match = buffer.mid(position, 32 );
             placeholder += QFileInfo(hashFile).fileName().length();

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

                ss << left << qSetFieldWidth(50) << QFileInfo(hashFile).fileName() << "FAIL" << qSetFieldWidth(0) << endl;
                test.prepend((s));
            }
          }
          /*
          for(int i=0; i<)
          QFile Check(name);
*/

      }


      ui->textBrowser->setText(test);


}




