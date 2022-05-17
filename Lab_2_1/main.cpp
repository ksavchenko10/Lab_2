#include <QCoreApplication>

#include "observer.h"
#include <stdio.h>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileObserver* obs;

    FSubject file("./test.txt");

    file.attach(obs);
    file.startNotify();

    return a.exec();
}
