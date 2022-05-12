#ifndef OBSERVER_H
#define OBSERVER_H

#include <QMainWindow>

class Observer : public QMainWindow
{
    Q_OBJECT

public:
    Observer(QWidget *parent = nullptr);
    ~Observer();
};
#endif // OBSERVER_H
