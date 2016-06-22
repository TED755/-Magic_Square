#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QCursor>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    currentMode = Menu;
    layout    = new QVBoxLayout(this);
    laylabel = new QHBoxLayout(this);
    table   =  new QTableView(this);
    start  = new QPushButton(this);
    end   = new QPushButton(this);
    str    =   new QLineEdit(this);
    labelPN   =    new QLabel(this);
    labelPT   =     new QLabel(this);
    labelIN = new QLabel(this);
    labelIT = new QLabel(this);
    delegate  =   new MagicDelegate();

    table->setItemDelegate(delegate);

    str->setDragEnabled(true);

    start->setText("Start game");
    start->setDefault(true);
    start->setEnabled(false);
    end->setText("End game");

    connect(start, SIGNAL(clicked(bool)), this, SLOT(startg()));
    connect(end, SIGNAL(clicked(bool)),this, SLOT(endg()));

    laylabel->addWidget(labelPT);
    laylabel->addWidget(labelPN);
    laylabel->addWidget(labelIT);
    laylabel->addWidget(labelIN);

    layout->addLayout(laylabel);
    layout->addWidget(str);
    layout->addWidget(table);
    layout->addWidget(start);
    layout->addWidget(end);

    end->hide();
    labelPN->hide();
    labelPT->hide();
    labelIN->hide();
    labelIT->hide();

    connect(str, SIGNAL(textChanged(QString)), this, SLOT(TextChanged(QString)));

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

    //count = model->OneMoreitcount;

    labelPT->setText("Порядок квадрата: ");
    labelPN->setNum(a);
    labelIT->setText("Осталось незаполненных ячеек: ");
    labelIN->setNum(model->ItemsCountModel());


    //labelIN->setNum(count);
    labelPT->show();
    labelPN->show();
    labelIT->show();

    table->setModel(model);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(ItemChanged()));
    labelIN->show();

    qDebug()<<"Build";    

}

void MainWindow::endg()
{
    int b = str->text().toInt();
    if (model->Full(b)){
        QMessageBox::information(this, "YOU WIN!", "IT'S MAGIC");
        qDebug() << "It's working!";
        window()->close();
    }
    else {
        QMessageBox::information(this, "Try again", "IT'S NOT MAGIC");
        qDebug()<< "Not magic";
    }
}

void MainWindow::TextChanged(QString str)
{
    int k = str.toInt();

    if(k > 2 && k < 5000)
        start->setEnabled(!str.isEmpty());
    else start->setEnabled(false);

}

void MainWindow::ItemChanged()
{
    labelIN->setNum(model->ItemsCountModel());
}

MainWindow::~MainWindow()
{
}
