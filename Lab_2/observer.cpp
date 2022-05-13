#include <observer.h>
#include <QFile>
#include <stdio.h>
#include <QString>


FileObserver::FileObserver()
{
}

void FileObserver::update(bool exist, bool new_exist, int size, int new_size)
{
    setlocale(LC_ALL, "Russian");

    if (new_exist != exist)
    {
        if (new_exist)
        {
            printf("Файл существует, файл не пустой. Размер = %d байт\n", new_size);
        }
        else
        {
            printf("Файл не существует\n");
        }

    }
    else
    {
        if (new_exist && new_size != size)
        {
            printf("Файл существует, файл был изменен. Новый размер = %d байт\n", new_size);
        }
        else if (!new_exist && size == -1)
        {
             printf("Файл не существует\n");
        }

    }
}
