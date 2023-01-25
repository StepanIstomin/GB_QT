#include "findthread.h"

FindThread::FindThread(QObject *parent)
    : QThread{parent}
{

}

void FindThread::run(FindFile* f)
{
    f->find();
}
