#include <QCoreApplication>

#include "observer.h"
#include <stdio.h>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileObserver* obs; //создаем экземпляр наблюдателя

    FSubject file("./test.txt"); //создаем экзепляр состояния файла

    file.attach(obs); //добавляем наблюдателя к экземпляру состояния файла
    file.startNotify(); //запускаем постоянную проверку состояния файла

    return a.exec();
}
