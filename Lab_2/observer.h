#ifndef OBSERVER_H
#define OBSERVER_H
#include <observer.cpp>
#include <iostream>
#include <QFile>
#include <QMainWindow>

class Observer
{
public:
    virtual void update() = 0;
};

class FileObserver: public Observer
{
    FileObserver();

    public:
        void update(bool exist, bool new_exist, int size, int new_size);
};


class FSubject: public QObject
{
    std::vector<FileObserver*> list;

    public:
    QString file_path;
    bool file_exist = false;
    int file_size = -1;

    FSubject(QString path);
    void attach(FileObserver *obs);
    void detach(FileObserver *obs);
    void startNotify();
    bool fileExist();
    float getSize();
    void notify();
};


#endif // OBSERVER_H
