#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>

#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QThread>




class GUIUpdater : public QObject {
    Q_OBJECT

public:
    explicit GUIUpdater(QObject *parent = 0) : QObject(parent) {}
   // void getHash(){ emit req(); }
    QString result2;
    QString dirSelect;
    QString checkoutput;


    //ProgressBar counting
    int numfiles, percent, counter = 0;


    enum Code{
        save,
        saveOld,
        check,
        checkOld,
        scan,
        none
    };

    Code test(QString method){
        if(method == "scan")
            return scan;
        if(method == "check")
            return check;
        if(method == "save")
            return save;
        if(method == "saveOld")
            return saveOld;
        if(method == "checkOld")
            return checkOld;
        return none;
    }



signals:
    void req();
    void Finished(QString);
    void percentChanged(int);
    void getfileTotal();
    void displayFileTotal(int); //update status bar
//    void finishedCheck();
//    void finishedSave();
    void close();

public slots:
   // void getpHash(){ emit req();}

    void getfileTotal(int total){
        numfiles = total;
        qDebug() << "GOT FILE TOTAL: " << numfiles << endl;
        emit displayFileTotal(numfiles);
    }

    //Determine Method to use
    void action(QString method){
        switch(test(method)){

        case scan:
            scanFile();
            break;
        case check:
            checkFile();
            break;
        case save:
            saveFile();
            break;
        case saveOld:
            oldSave();
            break;
        case checkOld:
            oldCheck();
            break;
        case none:
            break;
        }
    }



    //Change Directory
    void selectDir(QString dir){
        dirSelect = dir;
    }

    //Button Function Action
    void scanFile()
    {
        qDebug() << "PRESSED" << endl;
        QByteArray result;
        QString hash;
        QTextStream out(&result);

        //QDir dir = QDir::currentPath();
        QDir dir = dirSelect;
        qDebug() << "numfiles: " << numfiles << endl;
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
//                  hash = QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex();
//                  out << hash << " : " << dirIt.fileName() << "\n";

                  hash = QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex();
                  out << hash << "\t" << hashFile.fileName() << "\n";



                  qDebug() << "Filename: " << QFileInfo(hashFile).fileName() << endl;
                  qDebug() << "Hash: " << hash << endl;
                  counter++;
              }

              percent = counter * 100 / numfiles;
              emit percentChanged(percent);
              out.flush(); //Force output to show up immediately
          }

        qDebug() << "FILES: " << counter << endl;
        counter = 0;
        percent = 0;

          result2 = QString(result);
          emit Finished("scanFinished");
    }





    void checkFile(){
        QByteArray hash;
        QString fileName;


        QString hash_file;
        QVector<QString> hashes;
        QVector<QString> buffer;

        QFile sentry("sentry.dat");
        QDataStream in(&sentry);

        QString output;
        QString s;
        QTextStream ss(&s);

        if(sentry.open(QIODevice::ReadOnly)){
            in >> dirSelect;
            qDebug() << "Directory: " << dirSelect;
            while(!in.atEnd()){

                in >> hash >> fileName;
                hashes.append(hash.toHex());
                hashes.append(fileName);
            }
            //qDebug() << hashes;


        }

        int position;
        int counter = 0;
        emit getfileTotal();
        int totalwork = hashes.size() + numfiles;

        QDir dir = dirSelect;
        QDirIterator dirIt(dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories);
        {
            while(dirIt.hasNext()){
                dirIt.next();
                QFile hashFile(dirIt.filePath());
                if(hashFile.open(QIODevice::ReadOnly)){

                    hash_file = QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex();
                    fileName = hashFile.fileName();
                    buffer.append(fileName);

                    position = hashes.indexOf(fileName);

                    if(position != -1 && hashes.at(position-1) == hash_file){
//                        qDebug() << "HASH: " << hashes.at(hashes.indexOf(hash_file));
//                        qDebug() << "FILENAME: " << hashes.at(hashes.indexOf(hash_file)+1);
                        ss << left << qSetFieldWidth(50) << QFileInfo(hashFile).fileName() << "PASS" << qSetFieldWidth(0) << endl;
                        output.append(s);
                        s.clear();
                        checkoutput.append(QFileInfo(hashFile).fileName() + '\t' + hash_file + '\t' + "PASS" + '\n');
                    }
                    else if(QFileInfo(hashFile).fileName() == sentry.fileName()){
                        ss << left << qSetFieldWidth(50) << QFileInfo(hashFile).fileName() << "Sentry" << qSetFieldWidth(0) << endl;
                        output.prepend(s);
                        s.clear();
                        checkoutput.append(QFileInfo(hashFile).fileName() + '\t' + hash_file + '\t' +  "Sentry" + '\n');
                    }
                    else{
                        qDebug() << "FAIL: " << hashFile.fileName();
                        ss << left << qSetFieldWidth(50) << hashFile.fileName()/*QFileInfo(hashFile).fileName()*/ << "FAIL" << qSetFieldWidth(0) << endl;
                        output.prepend(s);
                        s.clear();
                        checkoutput.prepend(hashFile.fileName() + '\t'  + hash_file + '\t' + "FAIL" + '\n');

                    }
                }

                counter++;
                percent = counter * 100 / totalwork;
                emit percentChanged(percent);
                hash_file.clear();
            }
        }
            qDebug() << endl << endl;

        for(int i=1; i<hashes.size();i+=2)
        {
            qDebug() << hashes[i];
            if(buffer.indexOf(hashes[i]) == -1){
                ss << left << qSetFieldWidth(50) << hashes[i]/*QFileInfo(hashFile).fileName()*/ << "MISSING" << qSetFieldWidth(0) << endl;
                checkoutput.prepend(hashes[i] + '\t'  + hash[i-1] + '\t' + "MISSING" + '\n');

                output.prepend(s);
                s.clear();
               }
            percent = (i + 2 + counter) * 100 / totalwork;
            qDebug() << "i: " << i << "percent: " << percent;
            emit percentChanged(percent);
        }


        qDebug() << "Files: " << numfiles;
        qDebug() << "hashessize: " << hashes.size();
        result2 = output;
        emit Finished("checkFinished");


    }


    void saveFile(){
        QFile file("sentry.dat");



        //QTextStream out(&file);
        QDataStream out(&file);
        file.open(QIODevice::WriteOnly);
        //QDir dir = QDir::currentPath();
        QDir dir = dirSelect;

        out << dirSelect;
        //out << "Directory: " << dirSelect << endl; //prepend directory from which scan was selected to begin from

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
//                  out << QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5).toHex()
//                      << " : " << hashFile.fileName()/*dirIt.fileName()*/ << "\n";

                  out << QCryptographicHash::hash(hashFile.readAll(), QCryptographicHash::Md5) << hashFile.fileName();
                  counter++;
              }
              percent = counter * 100 / numfiles;
              emit percentChanged(percent);
              //out.flush(); //Force output to show up immediately
          }


        emit Finished("saveFinished");
        //ui->statusBar->show();
        //ui->statusBar->showMessage("Saved to sentry.dat!", 1000);
    }

    //Text mode
    void oldCheck(){

            qDebug() << "IN CHECK";
            QString buffer;
            QVector<QString> fileBuffer;
            QString match;
            QByteArray result;
            QString test;
            QString hash;
            int placeholder = 0;
            int position = 0;
            int totalwork = 0;
            int lines = 0; // Need to subtract one line to account for directory
            //ui->textBrowser->clear();

            QFile sentry("sentry.dat");
               if(sentry.open(QIODevice::ReadOnly))
               {
                   QTextStream in(&sentry);
                   while(!in.atEnd())
                   {
                       buffer += in.readLine() + "\n";
                       lines++;
                   }

                   sentry.close();
               }

            QTextStream out(result);


            int parse = 0;
            int parsepos = 0;
            int directory = 0; //find directory
            totalwork = numfiles + (buffer.length()-1) + (lines - 1);

            //FIND DIRECTORY
            directory = buffer.indexOf("Directory:",0);
            parse = buffer.indexOf("\n",directory);
            dirSelect = buffer.mid(11,parse-11);
            qDebug() << "PARSE! " << parse << endl;
            qDebug() << "Directory: " << dirSelect << endl;
            //



            //QDir dir = QDir::currentPath();
            QDir dir = dirSelect;
            emit getfileTotal();

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
                            checkoutput.append(QFileInfo(hashFile).fileName() + '\t'  + hash + '\t' + "PASS" + '\n');
                    }

                    else if(QFileInfo(hashFile).fileName() == sentry.fileName())
                    {
                            QString s;
                            QTextStream ss(&s);
                            ss << left << qSetFieldWidth(50) << QFileInfo(hashFile).fileName() << "SENTRY" << qSetFieldWidth(0) << endl;
                            test.append(qPrintable(s));
                            checkoutput.append(QFileInfo(hashFile).fileName() + '\t'  + hash + '\t' + "Sentry" + '\n');
                    }

                    else{
                            QString s;
                            QTextStream ss(&s);

                        ss << left << qSetFieldWidth(50) << hashFile.fileName()/*QFileInfo(hashFile).fileName()*/ << "FAIL" << qSetFieldWidth(0) << endl;
                        test.prepend((s));
                         checkoutput.prepend(hashFile.fileName() + '\t'  + hash + '\t' + "FAIL" + '\n');
                    }

                    counter++; //ProgressBar
                  }

                    percent = counter * 100 / totalwork;
                    emit percentChanged(percent);
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


                percent = (parse+counter) * 100 / (totalwork);
                emit percentChanged(percent);

        }


            qDebug() << "sentryBuffer: " <<  sentryBuffer.toList() << endl;
            qDebug() << "fileNames: " << fileBuffer.toList() << endl;
            qDebug() << buffer << endl;
            qDebug() << sentryBuffer.size() << endl;

            for(int i=0; i<sentryBuffer.size(); i++)
               {
                if(fileBuffer.indexOf(sentryBuffer.at(i)) == -1)
               {
                   ss << left << qSetFieldWidth(50) << sentryBuffer.at(i) << "MISSING" << qSetFieldWidth(0) << endl;
                   checkoutput.prepend(sentryBuffer.at(i) + '\t'  + " " + '\t' + "MISSING" + '\n');
                   //test.prepend(s);
                }
                counter++;

                percent = (parse+counter) * 100 / (totalwork);
                emit percentChanged(percent);
            }


              ss << left << qSetFieldWidth(50) << dirSelect << "DIRECTORY" << qSetFieldWidth(0) << endl;
              test.prepend(s);



              result2 = test;
              qDebug() << "PERCENT: " << percent << endl;
              counter = 0;percent=0;totalwork=0;

              qDebug() << "SENTRYBUFFEr: " << sentryBuffer.size() << endl;
              qDebug() << "ALAL: " << lines << endl;
              emit Finished("checkFinished");
              //ui->textBrowser->setText(test);


    }

    void oldSave(){
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
                      counter++;
                  }
                  percent = counter * 100 / numfiles;
                  emit percentChanged(percent);
                  out.flush(); //Force output to show up immediately
              }


            emit Finished("saveFinished");
            //ui->statusBar->show();
            //ui->statusBar->showMessage("Saved to sentry.dat!", 1000);
        }


};


#endif // WORKER_H





/*
void scanFile()
{
    qDebug() << "PRESSED" << endl;
    QByteArray result;
    QString hash;
    QTextStream out(&result);

    //QDir dir = QDir::currentPath();
    QDir dir = dirSelect;
    qDebug() << "numfiles: " << numfiles << endl;
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
              counter++;
          }

          percent = counter * 100 / numfiles;
          emit percentChanged(percent);
          out.flush(); //Force output to show up immediately
      }

    qDebug() << "FILES: " << counter << endl;
    counter = 0;
    percent = 0;

      result2 = QString(result);
      emit Finished("scanFinished");
}

*/
