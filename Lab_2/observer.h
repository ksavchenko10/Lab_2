#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <QFile>
#include <QMainWindow>

class Observer
{
public:
    virtual void Update();
};

class FileObserver: Observer
{
    public:
        void Update();
};

void FileObserver::Update()
{
   std::cout << "File was removed" << "\n";
}

class FSubject
{
    std::vector<FileObserver*> list;

    public:
    std::string filepath;
    std::QFile file;
    bool fileexist;
    float filesize;

    void attach(FileObserver *isfile);
    void detach(FileObserver *isfile);
    void notify();
    bool fileExist();
    bool sizeChanged();
};

bool FSubject::fileExist()
{
    this->fileexist = QFile(this->filepath).exists();
    return true;
}

bool FSubject::sizeChanged()
{
    float newsize = 0; //посчитать размер файала
    if (this->filesize != newsize)
    {
        return true;
    }

    return false;
}

#endif // OBSERVER_H
