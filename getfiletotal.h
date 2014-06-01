#ifndef GETFILETOTAL_H
#define GETFILETOTAL_H


#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDirIterator>


class GetFileTotal : public QObject{
    Q_OBJECT

public:
    int numfiles;
    QString dirSelect;

signals:
    void finished(int);
    void close();

    void disableScan();

public slots:

    void selectDir(QString dir){
        dirSelect = dir;
    }

    void getfileTotal(){

        emit disableScan(); //Disable Scan button until directory scanned

        QDir dir = dirSelect;
        numfiles = 0;
        QDirIterator dirIt(dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories);
          while(dirIt.hasNext())
          {
              dirIt.next();
              QFile lawl(dirIt.filePath());
              if(!lawl.open(QFile::ReadOnly)){
                }
              else
              {
                  numfiles++;
              }
          }
          emit finished(numfiles);
    }

};







#endif // GETFILETOTAL_H
