#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    currentMode = Menu;
    layout = new QVBoxLayout(this);
    layoutH = new QHBoxLayout(this);
    table = new QTableView(this);
    start = new QPushButton(this);
    end = new QPushButton(this);
    str = new QLineEdit(this);

    delegate = new MagicDelegate();
    table->setItemDelegate(delegate);

    start->setText("Start game");
    end->setText("End game");

    connect(start, SIGNAL(clicked(bool)), this, SLOT(startg()));
    connect(end, SIGNAL(clicked(bool)),this, SLOT(endg()));

    layout->addWidget(str);
    layout->addWidget(table);
    layout->addWidget(start);
    layout->addWidget(end);
    end->hide();
}


void MainWindow::startg()
{

    if(currentMode == Game)
        return;

    currentMode = Game;

    start->hide();
    end->show();


    int a = str->text().toInt();

    str->hide();
    delegate->SetMaxValue(a*a);

    model = new MagicSquareModel(a);
    model->insertColumns(0,a);
    model->insertRows(0, a);

    table->setModel(model);
    qDebug()<<"Build";    

}

void MainWindow::endg()
{
    int b = str->text().toInt();
    if (model->Full(b)){
        QMessageBox::information(this, "YOU WIN!", "IT'S MAGIC");
        qDebug() << "It's working!";
    }
    else {
        QMessageBox::information(this, "Try again", "IT'S NOT MAGIC");
        qDebug()<< "Not magic";
    }
}

MainWindow::~MainWindow()
{
}
