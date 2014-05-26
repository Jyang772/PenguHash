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

signals:
    void req();
    void Finished();

public slots:
    void getpHash(){ emit req();}

    void doWork()
    {
        qDebug() << "PRESSED" << endl;
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

          result2 = QString(result);
          emit Finished();
    }



};


#endif // WORKER_H
