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
    Mods mods;
    MagicSquareModel *model;
    QStandardItemModel* Startmodel;
    QTableView* table;
    QSpinBox* num;
    QComboBox* cmb;
    //QLineEdit* str;
    QStringList lst;

    QVBoxLayout* layout;
    QHBoxLayout* laylabel;

    QVBoxLayout* laynum;
    QVBoxLayout* laycompl;
    QHBoxLayout* sun;
    QVBoxLayout* main;

    QPushButton* start;
    QPushButton* end;
    QPushButton* exit;
    QPushButton* menuex;

    QLabel* labelnum;
    QLabel* labelcompl;

    QLabel* labelPN;//Показ порядка
    QLabel* labelPT;//Информация о порядке
    QLabel* labelIT;//показ оставшихся ячеек
    QLabel* labelIN;//Информация

    enum Mod {Game, Menu};
    Mod currentMode;

private slots:

    void game();
    void menu();
    void endg();
    void menuexs();
    void ItemChanged();
private:

    MagicDelegate *delegate;

};

#endif // MAINWINDOW_H
