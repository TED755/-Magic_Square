#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QLayout>
#include <QtWidgets>
#include <QWidget>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QSpinBox>
#include <QComboBox>
#include <QRadioButton>
#include <QGroupBox>
#include "magicsquaremodel.h"
#include "magicdelegate.h"
#include "mods.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //Mods mods;


    enum Mod {Game, Menu};
    Mod currentMode;
private:
    MagicSquareModel *model;
    QTableView* table;
    QSpinBox* num;
    QComboBox* cmb;
    QStringList lst;

    QMenuBar* mainMenu;
    QMenu* file;

    QVBoxLayout* mainLayout;//Главная компоновка
    QGridLayout* center;
    QHBoxLayout* layout;

    QPushButton* start;
    QPushButton* check;

    QLabel* labelnum;
    QLabel* labelcompl;

    QLabel* labelPN;//Показ порядка
    QLabel* labelPT;//Информация о порядке
    QLabel* labelIT;//показ оставшихся ячеек
    QLabel* labelIN;//Информация

    QLabel* labelmode;
    QRadioButton* arcade;
    QRadioButton* training;
    void createLayouts();
    void createMenu();

private slots:

    void menu();
    void game();    
    void endg();
    void menuexs();
    void ItemChanged();
private:

    MagicDelegate *delegate;

};

#endif // MAINWINDOW_H
