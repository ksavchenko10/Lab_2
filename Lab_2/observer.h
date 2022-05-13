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

void FSubject::attach(FileObserver *isfile)
{
    list.push_back(shop);
}

void FSubject::detach(FileObserver *isfile)
{
    list.erase(std::remove(list.begin(), list.end(), isfile), list.end());
}


void FSubject::notify()
{
    for (vector<FileObserver*>::const_iteratot iter = list.begin(); iter != list.end(); ++iter)
    {
        if (false) //если есть изменения
        {
            (*iter)->Update();
        }

    }
}

#endif // OBSERVER_H
