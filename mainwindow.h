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

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum MenuMod {Game, Menu};
    MenuMod currentMode;

    enum GameMode {Training, Arcade};
    GameMode gamemode;

private:
    QTime t;
    MagicSquareModel *model;
    QTableView* table;
    MagicDelegate *delegate;

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

    QLabel* labelPT;//Информация о порядке
    QLabel* labelIT;//показ оставшихся ячеек

    QLabel* labelmode;
    QRadioButton* arcade;
    QRadioButton* training;

    QHBoxLayout* HorizontalLayout;
    QGridLayout* ButtonsLay;

    void createLayouts();
    void createMenu();
    void createButtons();
    void countPoints();

    int points;
    int time;
    int SquareComlexity;
    int SquareNumber;

    vector<QPushButton*> buttons;

private slots:

    void menu();
    void game();    
    void endg();
    void menuexs();
    void ItemChanged();
    void inputInformation();
    void arcadeMode();
    void trainingMode();
};

#endif // MAINWINDOW_H
