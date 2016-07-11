#include "mainwindow.h"
#include <QPalette>
//#include "magicsquare.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    int Light;

//    Light

    /*QPalette pal(Qt::darkYellow)*/;

    //a.setPalette(pal);

    w.setGeometry(600, 200, 500, 400);

    w.show();

    return a.exec();
}
