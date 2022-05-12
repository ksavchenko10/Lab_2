#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>

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


#endif // OBSERVER_H
