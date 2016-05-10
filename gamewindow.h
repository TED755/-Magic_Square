#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
//#include <QApplication>>

class GameWindow : public QMainWindow

{
    Q_OBJECT


public :
    GameWindow(QWidget *MainWindow = 0);
    ~GameWindow();


};

#endif // GAMEWINDOW_H

