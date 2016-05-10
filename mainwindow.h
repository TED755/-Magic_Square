#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QLayout>
#include <QtWidgets>
#include <QWidget>
#include "magicsquaremodel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MagicSquareModel *model;
    QStandardItemModel* Startmodel;
    QTableView* table;
    QLineEdit* str;
    QLineEdit* str1;
    QVBoxLayout* layout;
    QHBoxLayout* layoutH;
    QPushButton* start;

    enum Mod {Game, Menu};
    Mod currentMode;

private slots:

    void startg();

    //void zero(QTableView* table);
};

#endif // MAINWINDOW_H
