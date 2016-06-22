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
