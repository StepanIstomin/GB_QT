#ifndef FINDTHREAD_H
#define FINDTHREAD_H


#include <QThread>
#include <findfile.h>

class FindThread : public QThread
{
public:
    explicit FindThread(QObject *parent = nullptr);
    void run(FindFile* f) override;
};

#endif // FINDTHREAD_H
