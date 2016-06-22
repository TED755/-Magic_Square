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
    QSpinBox* num;
    QComboBox* cmb;
    QLineEdit* str;

    QVBoxLayout* layout;
    QHBoxLayout* laylabel;

    QVBoxLayout* laynum;
    QVBoxLayout* laycompl;
    QHBoxLayout* sun;
    QVBoxLayout* main;

    QPushButton* start;
    QPushButton* end;

    QLabel* labelnum;
    QLabel* labelcompl;

    QLabel* labelPN;//Показ порядка
    QLabel* labelPT;//Информация о порядке
    QLabel* labelIT;//показ оставшихся ячеек
    QLabel* labelIN;//Информация

    enum Mod {Game, Menu};
    Mod currentMode;

private slots:

    void startg();
    void endg();
    void TextChanged(QString str);
    void ItemChanged();
private:

    MagicDelegate *delegate;

};

#endif // MAINWINDOW_H
