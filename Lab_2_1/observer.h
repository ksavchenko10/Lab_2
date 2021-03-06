#ifndef OBSERVER_H
#define OBSERVER_H
#include <QFile>
#include <stdio.h>
#include <QString>
#include <vector>
#include <Qtimer.h>
#include <thread>



class Observer //класс наблюдатель
{
public:
    virtual void update() = 0;

};

class FileObserver: public Observer //конкретный класс наблюдатель за файлами
{
    FileObserver();

    public:
        void update(bool exist, bool new_exist, int size, int new_size);
};

class FSubject: public QObject //класс для работы с файлом
{
    std::vector<FileObserver*> list; //вектор наблюдателей

    public:
    QString file_path; //путь к файлу
    bool file_exist = false; //флаг состояние файла (существует/не сущетсвует)
    int file_size = -1; //размер файла

    FSubject(QString path); //конструктор
    void attach(FileObserver *obs); //добавить наблюдателя
    void detach(FileObserver *obs); //убрать наблюдателя
    void startNotify(); //запустить постоянную проверку
    bool fileExist(); //метод возвращающий существует файл или нет
    float getSize(); //метод возвращающий размер файла
    void notify(); //метод единоразовой проверки состояния файла и вызова метода наблюдателей
};

FileObserver::FileObserver() //конструктор
{
}


void FileObserver::update(bool exist, bool new_exist, int size, int new_size) //вывод изменений
{
    //setlocale(LC_ALL, "Russian");

    if (new_exist != exist) //если изменился статус существования файла
    {
        if (new_exist) //если файл существует
        {
            printf("The file exists, the file is not empty. Size = %d bytes\n", new_size);
        }
        else //если файла нет
        {
            printf("File does not exist\n");
        }

    }
    else //если статус существования не изменился
    {
        if (new_exist && new_size != size) //если существует и изменился размер
        {
            printf("The file exists, the file has been modified. New size = %d bytes\n", new_size);
        }
        else if (!new_exist && size == -1) //если не существует и это первая проверка, после первой проверки размер станет >=0
        {
             printf("File does not exist\n");
        }

    }
}


FSubject::FSubject(QString path)
{
    this->file_path = path; //запоминаем путь к файлу
}

bool FSubject::fileExist()
{
     if (QFile(this->file_path).exists()) //если файл по заданному пути  существует
     {
         return true;
     }

    return false;
}

float FSubject::getSize()
{
    int size = 0;
    size = QFile(this->file_path).size(); //берем размер файла в байтах

    return size;
}


void FSubject::attach(FileObserver *obs)
{
    list.push_back(obs); //добавляем наблюдателя в наш вектор
}

void FSubject::detach(FileObserver *obs)
{
    list.erase(std::remove(list.begin(), list.end(), obs), list.end()); //удаляем наблюдателя из вектора
}


void FSubject::startNotify() //запускаем постоянную проверку файла
{
  while(true)
  {
     this->notify(); //вызываем метод проверки файла
     std::this_thread::sleep_for(std::chrono::milliseconds(100)); //пауза 100 миллисекунд
  }
}


void FSubject::notify()
{
    bool new_exist = this->fileExist(); //вычисляем существование файла
    int new_size = this->getSize(); //вычисляем размер файла

    //пробегаем по всем наблюдателям в нашем списке
    for (std::vector<FileObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        (*iter)->update(this->file_exist, new_exist, this->file_size, new_size); //зпускаем у наблюдателей метод update для вывода информации о изменениях
    }

    this->file_exist = new_exist; //запоминаем новое состояние файла
    this->file_size = new_size; //запоминаем новый размер файла
}
#endif // OBSERVER_H
