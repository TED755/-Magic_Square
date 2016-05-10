#include "mainwindow.h"
//#include "magicsquare.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setGeometry(600, 200, 500, 400);

    w.show();

    return a.exec();
}
