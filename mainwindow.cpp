#include <QDebug>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    currentMode = Menu;
    layout = new QVBoxLayout(this);
    layoutH = new QHBoxLayout(this);
    //Startmodel = new QStandardItemModel(this);
    table = new QTableView(this);
    start = new QPushButton(this);
    str = new QLineEdit(this);

    delegate = new MagicDelegate();
    table->setItemDelegate(delegate);

    //QModelIndex i(1,1,[](){return;},model->m);

    //table->edit(i);
    //str1 = new QLineEdit(this);

    //QModelIndex index = model->index(1,2, QModelIndex());

    //QVariant value = model->data(index);
    //qDebug() << value;
    start->setText("Start game");
    connect(start, SIGNAL(clicked(bool)), this, SLOT(startg()));
    layout->addWidget(str);
    //layout->addWidget(str1);

    //table->setModel(Startmodel);
    layout->addWidget(table);
    //layout->addWidget(layoutH);
    layout->addWidget(start);

    //QTableModel *m = new QTableModel(this);
}


void MainWindow::startg()
{

    if(currentMode == Game)
        return;

    currentMode = Game;

    int a = str->text().toInt();//, b = str1->text().toInt();
    delegate->SetMaxValue(a*a);
    //table->setModel(model);
    //Startmodel->insertColumns(0,a);
    //Startmodel->insertRows(0,a);
    model = new MagicSquareModel(a);
    model->insertColumns(0,a);
    model->insertRows(0, a);
    table->setModel(model);
    qDebug()<<"Build";    

}

MainWindow::~MainWindow()
{
}
