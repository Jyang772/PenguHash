#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getCheckSum();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::getCheckSum()
{


       int counter = 0;
       QDir dir = QDir::currentPath();
       QCryptographicHash hash( QCryptographicHash::Sha1);

       //Create sentry file

       QFile sentry("sentry.dat");

       sentry.open(QIODevice::WriteOnly | QIODevice::Text);
       QTextStream out(&sentry);


       QDirIterator iterator(dir.absolutePath(), QDirIterator::Subdirectories);
       while (iterator.hasNext()) {
          iterator.next();

          counter++;

              QFile file(iterator.next());

               if ( file.open( QIODevice::ReadOnly ) ) {
                   hash.addData( file.readAll() );
                   sig = hash.result();

                   if(!savetoFile)
                   ui->textBrowser->append(QFileInfo(file).fileName() + ": " + QString(sig.toHex()));

                   if(savetoFile)
                   out << QFileInfo(file).fileName() + " : " + QString(sig.toHex()) << endl;

               } else {
                   qDebug() << "Can't open " << QFileInfo(file).fileName() << endl;
               }
       }


        savetoFile = false;

}

void MainWindow::on_pushButton_clicked()
{
   // getCheckSum();

    ui->textBrowser->clear();
    int counter = 0;
    int placeholder;
    QString match;

    //Open sentry.dat to check

    QFile sentry("sentry.dat");
    if(sentry.open(QIODevice::ReadOnly))
    {
        QTextStream in(&sentry);
        while(!in.atEnd())
        {
            buffer += in.readLine();
            counter++;
        }

        sentry.close();
    }

    qDebug() << buffer << endl;
    qDebug() << "Files: " << counter << endl;



    QCryptographicHash hash( QCryptographicHash::Sha1);
    QDir dir = QDir::currentPath();
    QDirIterator iterator(dir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
       iterator.next();

       counter++;

           QFile file(iterator.next());

            if ( file.open( QIODevice::ReadOnly ) ) {
                hash.addData( file.readAll() );
                sig = hash.result();

                qDebug() << buffer.indexOf(QFileInfo(file).fileName()) << endl;
                placeholder = buffer.indexOf(QFileInfo(file).fileName());
                qDebug() << "FileName: " << QFileInfo(file).fileName() << endl;
                qDebug() << "HASH: " << buffer.mid(placeholder + QFileInfo(file).fileName().length() + 3,40) << endl;
                qDebug() << "HASH2: " << sig.toHex() << endl;
                match = buffer.mid(placeholder + QFileInfo(file).fileName().length() + 3,40);



                if(sig.toHex()== match){

                    ui->textBrowser->append(QFileInfo(file).fileName() + " PASS!");

                   }
                else
                    ui->textBrowser->append(QFileInfo(file).fileName() + " FAIL!");





            } else {
            }
    }

}



void MainWindow::on_pushButton_2_clicked()
{
    savetoFile = true;
    getCheckSum();
    ui->statusBar->show();
    ui->statusBar->showMessage("Saved to sentry.dat!", 10);
}
