#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setGeometry(600, 200, 640, 480);

    w.show();

    return a.exec();
}
/*==========================ПЛАН===========================
 * Завести базу данных игроков
 * Выделение ячеек
 * Переписать формулу подсчета очков
 * +доплнительно: поправить интерфейс таблицы; испраивить баг проверки ячеек*/
