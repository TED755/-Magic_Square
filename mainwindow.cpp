#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
/*menu*/
    currentMode = Menu;
    layout    = new QVBoxLayout(this);
    laylabel = new QHBoxLayout(this);

    table   =  new QTableView(this);
    start  = new QPushButton(this);
    end   = new QPushButton(this);
    str    =   new QLineEdit(this);
    num = new QSpinBox(this);
    cmb = new QComboBox(this);
    labelPN   =    new QLabel(this);
    labelPT   =     new QLabel(this);
    labelIN = new QLabel(this);
    labelIT = new QLabel(this);
    delegate  =   new MagicDelegate();

    laycompl = new QVBoxLayout(this);
    laynum = new QVBoxLayout(this);
    sun = new QHBoxLayout(this);
    main = new QVBoxLayout(this);

    labelnum = new QLabel(this);
    labelcompl = new QLabel(this);

    table->setItemDelegate(delegate);

    labelcompl->setText("Complexity");
    labelnum->setText("Number");

    num->setMinimum(3);
    num->setMaximum(1000);

    //str->setDragEnabled(true);
    str->hide();

    start->setText("Start game");
    start->setDefault(true);
    //start->setEnabled(true);
    end->setText("End game");

    connect(start, SIGNAL(clicked(bool)), this, SLOT(startg()));
    connect(end, SIGNAL(clicked(bool)),this, SLOT(endg()));

    laycompl->addWidget(labelcompl);
    laycompl->addWidget(cmb);
    laynum->addWidget(labelnum);
    laynum->addWidget(num);
    sun->addLayout(laycompl);
    sun->addLayout(laynum);
    main->addLayout(sun);
    main->addWidget(start);


    laylabel->addWidget(labelPT);
    laylabel->addWidget(labelPN);
    laylabel->addWidget(labelIT);
    laylabel->addWidget(labelIN);

    layout->addLayout(laylabel);
    layout->addLayout(main);
    layout->addWidget(table);
    //layout->addWidget(start);
    layout->addWidget(end);

    table->hide();
    end->hide();
    labelPN->hide();
    labelPT->hide();
    labelIN->hide();
    labelIT->hide();

    //connect(str, SIGNAL(textChanged(QString)), this, SLOT(TextChanged(QString)));

}

/*game*/
void MainWindow::startg()
{

    if(currentMode == Game)
        return;

    currentMode = Game;



    start->hide();
    num->hide();
    cmb->hide();
    end->show();
    table->show();


    int a = num->text().toInt();

    str->hide();
    num->hide();

    delegate->SetMaxValue(a*a);

    model = new MagicSquareModel(a);
    model->insertColumns(0,a);
    model->insertRows(0, a);

    labelPT->setText("Порядок квадрата: ");
    labelPN->setNum(a);
    labelIT->setText("Осталось незаполненных ячеек: ");
    labelIN->setNum(model->ItemsCountModel());

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
    int b = num->text().toInt();
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
