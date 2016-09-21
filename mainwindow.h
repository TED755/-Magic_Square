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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QMainWindow* mainwinow;

    enum MenuMod {Game, Menu};
    MenuMod currentMode;

    enum GameMode {Training, Arcade};
    GameMode gamemode;

private:
    QWidget* MainWidget;
    QWidget* NumberWidget;
    QWidget* ComlWidget;
    QWidget* ModeWidget;
    QWidget* SettingWidget;
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

    QWidget* GameWidget;

    QPushButton* start;
    QPushButton* check;

    QLabel* labelnum;
    QLabel* labelcompl;

    QLabel* labelPT;//Информация о порядке
    QLabel* labelIT;//показ оставшихся ячеек

    QLabel* aboutNumlabel;
    QListWidget* numbersList;

    QLabel* labelmode;
    QRadioButton* arcade;
    QRadioButton* training;

    QHBoxLayout* HorizontalLayout;
    QGridLayout* ButtonsLay;

//    QPushButton* checkLastNumber;

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
