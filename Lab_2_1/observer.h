#ifndef OBSERVER_H
#define OBSERVER_H
#include <QFile>
#include <stdio.h>
#include <QString>
#include <vector>
#include <Qtimer.h>
#include <thread>



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

FileObserver::FileObserver()
{
}


void FileObserver::update(bool exist, bool new_exist, int size, int new_size)
{
    //setlocale(LC_ALL, "Russian");

    if (new_exist != exist)
    {
        if (new_exist)
        {
            printf("The file exists, the file is not empty. Size = %d bytes\n", new_size);
        }
        else
        {
            printf("File does not exist\n");
        }

    }
    else
    {
        if (new_exist && new_size != size)
        {
            printf("The file exists, the file has been modified. New size = %d bytes\n", new_size);
        }
        else if (!new_exist && size == -1)
        {
             printf("File does not exist\n");
        }

    }
}


FSubject::FSubject(QString path)
{
    this->file_path = path;
}

bool FSubject::fileExist()
{
     if (QFile(this->file_path).exists())
     {
         return true;
     }

    return false;
}

float FSubject::getSize()
{
    int size = 0;
    size = QFile(this->file_path).size();

    return size;
}


void FSubject::attach(FileObserver *obs)
{
    list.push_back(obs);
}

void FSubject::detach(FileObserver *obs)
{
    list.erase(std::remove(list.begin(), list.end(), obs), list.end());
}


void FSubject::startNotify()
{
  while(true)
  {
     this->notify();
     std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}


void FSubject::notify()
{
    bool new_exist = this->fileExist();
    int new_size = this->getSize();


    for (std::vector<FileObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        (*iter)->update(this->file_exist, new_exist, this->file_size, new_size);
    }

    this->file_exist = new_exist;
    this->file_size = new_size;
}
#endif // OBSERVER_H
