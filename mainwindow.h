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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    enum MenuMod {Game, Menu};
    MenuMod currentMode;

    enum GameMode {Training, Arcade};
    GameMode gamemode;

private:
    QWidget* NumberWidget;//порядок
    QWidget* ComplWidget;//сложность
    QWidget* ModeWidget;//режим
    QWidget* SettingWidget;//общий

    QTime t;
    MagicSquareModel *model;
    QTableView* table;
    MagicDelegate *delegate;

    QSpinBox* num;
    QComboBox* cmb;
    QStringList lst;

    QMenuBar* MenuBar;
    QMenu* file;
    QMenu* about;

    QPushButton* start;
    QPushButton* check;

    QLabel* labelnum;
    QLabel* labelcompl;
    QLabel* labelmode;

    QLabel* labelPT;//Информация о порядке
    QLabel* labelIT;//показ оставшихся ячеек

    QLabel* aboutNumlabel;
    QListWidget* numbersList;

    QRadioButton* arcade;
    QRadioButton* training;

    QHBoxLayout* HorizontalLayout;
    QGridLayout* ButtonsLay;

    QPushButton* checkLastNumber;

    QVBoxLayout* mainLayout;
    QLabel* welcome;

    QVBoxLayout* infoW;

    void createMenu();
    void countPoints();
    void createLayouts();
    void setSettings();
    void hideMenu();
    void hideGame();
    void FreeMemory();

    int points;
    int time;
    int SquareComlexity;
    int SquareNumber;

    bool flag = false;

private slots:

    void menu();
    void game();
    void endg();
    void menuexs();
    void ItemChanged();
    void inputInformation();
    void arcadeMode();
    void trainingMode();
    void numbersListsSlot();

    void aboutDevelopers();
    void aboutSquares();
    void aboutRules();
};

#endif // MAINWINDOW_H
