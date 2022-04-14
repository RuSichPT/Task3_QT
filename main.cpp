#include "mainwindow.h"
#include "mythread.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MyThread t(&w);
    t.start();
    int result = a.exec();
    t.terminate();
    return result;
}
