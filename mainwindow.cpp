#include <QDebug>
#include "mainwindow.h"
#include "magicdelegate.h"

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

    table->setItemDelegate(new MagicDelegate());

    //QModelIndex i(1,1,[](){return;},model->m);

    //table->edit(i);
    //str1 = new QLineEdit(this);

    //QModelIndex index = model->index(1,2, QModelIndex());

    //QVariant value = model->data(index);
    //qDebug() << value;
    start->setText("Warning: Pointless Button");
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
    //table->setModel(model);
    //Startmodel->insertColumns(0,a);
    //Startmodel->insertRows(0,a);
    model = new MagicSquareModel(a);
    model->insertColumns(0,a);
    model->insertRows(0, a);
    table->setModel(model);
    qDebug()<<"Build";
    for(int i = 0; i < a; i++)
        for(int j = 0; j < a; j++)
        {
            //qDebug() << "enter";
            QModelIndex ind = model->index(i,j);

            model->setData(ind, 0);

            model->setData(ind, QFont("Arial", 15,50) , Qt::FontRole);
            model->setData(ind,QBrush(Qt::red),Qt::BackgroundRole);
        }

}

MainWindow::~MainWindow()
{
}
