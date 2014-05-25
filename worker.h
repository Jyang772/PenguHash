#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class GUIUpdater : public QObject {
    Q_OBJECT

public:
    explicit GUIUpdater(QObject *parent = 0) : QObject(parent) {}
    void getHash(){ emit req(); }

signals:
    void req();
};


#endif // WORKER_H
