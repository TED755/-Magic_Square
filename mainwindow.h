#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QLayout>
#include <QtWidgets>
#include <QWidget>
#include <QTableWidget>
#include "magicsquaremodel.h"
#include "magicdelegate.h"

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
    QVBoxLayout* layout;
    QHBoxLayout* laylabel;
    QPushButton* start;
    QPushButton* end;
    QLabel* label;
    QLabel* label2;

    enum Mod {Game, Menu};
    Mod currentMode;

private slots:

    void startg();
    void endg();
    void TextChanged(QString str);

private:

    MagicDelegate *delegate;

};

#endif // MAINWINDOW_H
